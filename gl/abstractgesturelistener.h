#ifndef ABSTRACTGESTURELISTENER_H
#define ABSTRACTGESTURELISTENER_H

#include <QObject>
#include "gda/abstractgda.h"

class AbstractGestureListener: public QObject
{
	Q_OBJECT
	
public:
	explicit AbstractGestureListener(QObject *parent = 0);
	
	void listen(AbstractGDA* algo);
	
	~AbstractGestureListener();
	
protected:
	virtual void onGestureDetected(int gestureId) = 0;
	
private slots:
	void gestureDetected(int gestureId);
	
private:
	AbstractGDA* gda;
	
};

#endif // ABSTRACTGESTURELISTENER_H
