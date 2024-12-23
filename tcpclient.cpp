#include "TcpClient.h"

TcpClient::TcpClient(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onDataReceived);
    connect(socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
}

bool TcpClient::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

bool TcpClient::connectToServer(const QString &host, quint16 port)
{
    if (isConnected()) {
        qDebug() << "Вы уже подключены к серверу";
        return false;
    }

    if (!socket) {
        qCritical() << "Ошибка: socket не инициализирован";
        return false;
    }

    qDebug() << "Подключение к серверу:" << host << port;
    socket->connectToHost(host, port);

    if (socket->waitForConnected(5000)) {
        qDebug() << "Успешно подключено к серверу:" << host << port;
        return true;
    } else {
        qWarning() << "Не удалось подключиться к серверу:" << host << port
                   << "- Ошибка:" << socket->errorString();
        return false;
    }
}

void TcpClient::disconnectFromServer()
{
    if (isConnected()) {
        qDebug() << "Отключение от сервера";
        socket->disconnectFromHost();

        if (socket->waitForDisconnected(5000)) {
            qDebug() << "Успешно отключено от сервера";
        } else {
            qWarning() << "Не удалось отключиться от сервера, ошибка:" << socket->errorString();
        }
    } else {
        qDebug() << "Не подключены к серверу, отключение не требуется";
    }
}

void TcpClient::sendData(const QByteArray &data)
{
    if (isConnected()) {
        qDebug() << "Отправка данных: " << data;
        socket->write(data);
    }
    else {
        qWarning() << "Отправка невозможна, не подключены к серверу";
    }
}

void TcpClient::onConnected()
{
    qDebug() << "Подключен к серверу.";
}

void TcpClient::onDisconnected()
{
    qDebug() << "Отключен от сервера.";
    emit disconnected();
}

void TcpClient::onDataReceived()
{
    QByteArray data = socket->readAll();
    emit dataReceived(data);
    qDebug() << "Ответ от сервера:" << data;
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    emit disconnected();
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qWarning() << "Удалённый хост закрыл соединение!";
        break;
    case QAbstractSocket::HostNotFoundError:
        qWarning() << "Хост не найден!";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qWarning() << "Подключение отклонено!";
        break;
    default:
        qWarning() << "Ошибка сокета:" << socket->errorString();
        break;
    }
}
