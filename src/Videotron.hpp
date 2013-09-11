#ifndef Videotron_HPP_
#define Videotron_HPP_

#include <QObject>
#include <QFile>
#include <bb/platform/HomeScreen>
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/ListView>
#include <bb/cascades/QMLDocument>
#include <QSettings>

using namespace bb::cascades;

namespace bb {
namespace cascades {
class Application;
class LocaleHandler;
}
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class Videotron: public QObject {
	Q_OBJECT
public:
	Videotron(bb::cascades::Application *app);Q_INVOKABLE
	void initiateRequests();Q_INVOKABLE
	bool isAvailable(QString userName);Q_INVOKABLE
	void showInfoToast(QString title, QString body);
	bool checkSchedule();

	/* Invokable functions that we can call from QML*/

	/**
	 * This Invokable function gets a value from the QSettings,
	 * if that value does not exist in the QSettings database, the default value is returned.
	 *
	 * @param objectName Index path to the item
	 * @param defaultValue Used to create the data in the database when adding
	 * @return If the objectName exists, the value of the QSettings object is returned.
	 *         If the objectName doesn't exist, the default value is returned.
	 */
	Q_INVOKABLE
	QString getValueFor(const QString &objectName, const QString &defaultValue);

	/**
	 * This function sets a value in the QSettings database. This function should to be called
	 * when a data value has been updated from QML
	 *
	 * @param objectName Index path to the item
	 * @param inputValue new value to the QSettings database
	 */
	Q_INVOKABLE
	void saveValueFor(const QString &objectName, const QString &inputValue);

	QString downloadBandwith;
	QString uploadBandwith;
	QString totalBandwith;
	QString titre_consommation;

	virtual ~Videotron() {
	}

private slots:
	void onSystemLanguageChanged();
	void requestFinished(QNetworkReply* reply);

private:
	QTranslator* m_pTranslator;
	bb::cascades::LocaleHandler* m_pLocaleHandler;
	QNetworkAccessManager* mNetworkAccessManager;
	void searchWebpage(QString searchdata);
	QFile* mFile;
	QSettings setting;
	ActivityIndicator* activity;
};

#endif /* Videotron_HPP_ */
