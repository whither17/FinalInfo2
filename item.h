#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "player.h"

class item : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    item(int tipo_);
    void cutSprites(QString name);
    int getTipo() const;

public slots:
    void checkCollitions();

signals:
    void power(int p);

private:
    int tipo;
    bool uso;
    QTimer *live;
    QList<QGraphicsItem*> collitions;
    QMediaPlayer *sound;
    QAudioOutput *audioOutput;
};

#endif // ITEM_H
