#include "Videotron.hpp"
#include "ActiveFrameQML.hpp"

#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/system/SystemToast>
#include <bb/system/SystemDialog>
#include <bb/cascades/Label>

using namespace bb::cascades;

QString videotronURL;
QObject* downloadLabel;
QObject* uploadLabel;
QObject* totalLabel;
QObject* consommationLabel;

Videotron::Videotron(bb::cascades::Application *app) :
		QObject(app) {

	// prepare the localization
	m_pTranslator = new QTranslator(this);
	m_pLocaleHandler = new LocaleHandler(this);
	if (!QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()),
			this, SLOT(onSystemLanguageChanged()))) {
		// This is an abnormal situation! Something went wrong!
		// Add own code to recover here
		qWarning() << "Recovering from a failed connect()";
	}
	// initial load
	onSystemLanguageChanged();

	// Create scene document from main.qml asset, the parent is set
	// to ensure the document gets destroyed properly at shut down.
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("app", this);

	ActiveFrameQML *activeFrame = new ActiveFrameQML();
	Application::instance()->setCover(activeFrame);

	qml->setContextProperty("activeFrame", activeFrame);

	// Create root object for the UI
	AbstractPane* root = qml->createRootObject<AbstractPane>();

	activity = root->findChild<ActivityIndicator*>("indicator");
	downloadLabel = root->findChild<Label*>("downloadLabel");
	uploadLabel = root->findChild<Label*>("uploadLabel");
	//totalLabel = root->findChild<Label*>("totalLabel");
	consommationLabel = root->findChild<Label*>("titre_consommation");

	if(checkSchedule()){
		mNetworkAccessManager = new QNetworkAccessManager(this);

		bool result = connect(mNetworkAccessManager,
				SIGNAL(finished(QNetworkReply*)), this,
				SLOT(requestFinished(QNetworkReply*)));
		Q_ASSERT(result);
		Q_UNUSED(result);

		videotronURL = setting.value("videotronURL").toString() + setting.value("username").toString();
		activity->start();
		initiateRequests();

	}
	else {
		showInfoToast("Services Restreints", "Vidéotron offre momentanément des services restreints en raison de travaux de maintenance de nos systèmes.");
	}

	// Set created root object as the application scene
	app->setScene(root);
}

void Videotron::onSystemLanguageChanged() {
	QCoreApplication::instance()->removeTranslator(m_pTranslator);
	// Initiate, load and install the application translation files.
	QString locale_string = QLocale().name();
	QString file_name = QString("Videotron_%1").arg(locale_string);
	if (m_pTranslator->load(file_name, "app/native/qm")) {
		QCoreApplication::instance()->installTranslator(m_pTranslator);
	}
}

void Videotron::initiateRequests() {
	//activity->start();
	QNetworkRequest request = QNetworkRequest();
	request.setUrl(QUrl(videotronURL));
	mNetworkAccessManager->get(request);
}

void Videotron::requestFinished(QNetworkReply* reply) {
	QString replyRedirect = reply->attribute(
			QNetworkRequest::RedirectionTargetAttribute).toString();
	if (replyRedirect != "") {
		videotronURL = replyRedirect;
		initiateRequests();
	} else {
		if (reply->error() == QNetworkReply::NoError) {
			const QByteArray response(reply->readAll());

			const char* cString = response.constData();
			QString responseString = QString::fromUtf8(cString);

			QFile file(QDir::currentPath() + "/data/index.html");
			file.open(QIODevice::WriteOnly);
			QTextStream out(&file);
			out << responseString;
			file.close();

			searchWebpage(responseString);
		} else {
			qDebug() << "\n Problem with the network";
			qDebug() << "\n" << reply->errorString();
		}
	}
	reply->deleteLater();
}

void Videotron::searchWebpage(QString stringdata) {
	qDebug() << stringdata;
	if (!stringdata.contains("download_label")) {
		bool result = isAvailable("test");
		Q_UNUSED(result);
		showInfoToast("Le compte n'existe pas.", "Compte inexistant");
	} else {
		//Grabbing the Download label
		int indexBegin = stringdata.indexOf("download_label", 0) + 91;
		int indexEnd = stringdata.indexOf("&nbsp;", indexBegin);
		downloadBandwith = stringdata.mid(indexBegin, indexEnd - indexBegin);

		qDebug() << "Download: " << downloadBandwith;
		downloadLabel->setProperty("text", downloadBandwith + " GB");

		//Grabbing the Upload label
		indexBegin = stringdata.indexOf("upload_label", 0) + 87;
		indexEnd = stringdata.indexOf("&nbsp;", indexBegin);
		uploadBandwith = stringdata.mid(indexBegin, indexEnd - indexBegin);

		qDebug() << "Upload: " << uploadBandwith;
		uploadLabel->setProperty("text", uploadBandwith + " GB");

		//Grabbing the Total label
		indexBegin = stringdata.indexOf("total_label", 0) + 104;
		indexEnd = stringdata.indexOf("&nbsp;", indexBegin);
		totalBandwith = stringdata.mid(indexBegin, indexEnd - indexBegin);

		qDebug() << "Total: " << totalBandwith;

		indexBegin = stringdata.indexOf("titre_consommation", 0) + 48;
		indexEnd = stringdata.indexOf("/h3", indexBegin) - 1;
		titre_consommation = stringdata.mid(indexBegin, indexEnd - indexBegin);
		consommationLabel->setProperty("text", titre_consommation);

		qDebug() << "Consommation: " << titre_consommation;

		activity->stop();
	}
}

void Videotron::showInfoToast(QString title, QString body) {
	bb::system::SystemDialog* toast = new bb::system::SystemDialog("OK", this);
	toast->setBody(body);
	toast->setTitle(title);
	toast->show();
}

bool Videotron::isAvailable(QString userName) {
	Q_UNUSED(userName);
	return true;
}

QString Videotron::getValueFor(const QString &objectName, const QString &defaultValue)
{
    // If no value has been saved, return the default value.
    if (setting.value(objectName).isNull()) {
        return defaultValue;
    }

    // Otherwise, return the value stored in the settings object.
    return setting.value(objectName).toString();
}

void Videotron::saveValueFor(const QString &objectName, const QString &inputValue)
{
    // A new value is saved to the application settings object.
    setting.setValue(objectName, QVariant(inputValue));
}

bool Videotron::checkSchedule()
{
	int scheduleTimeLower = getValueFor(QDate::currentDate().longDayName(QDate::currentDate().dayOfWeek()).toLower(), "").split("|")[0].toInt();
	int scheduleTimeHigher = getValueFor(QDate::currentDate().longDayName(QDate::currentDate().dayOfWeek()).toLower(), "").split("|")[1].toInt();
	int nowTime = QTime::currentTime().hour();

	return (nowTime >= scheduleTimeLower && nowTime <= scheduleTimeHigher);
}
