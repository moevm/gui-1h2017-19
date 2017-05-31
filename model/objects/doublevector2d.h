#ifndef DOUBLEVECTOR2D_H
#define DOUBLEVECTOR2D_H


class DoubleVector2D
{
private:
    double x;
    double y;

    double size;
    double angle;

    void polarToRectangular();
    void rectangularToPolar();

public:
    DoubleVector2D(double size = 0,
                   double angle = 0);
    DoubleVector2D(const DoubleVector2D & vec);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getSize() const;
    void setSize(double value);

    double getAngle() const;
    void setAngle(double value);
};

#endif // DOUBLEVECTOR2D_H
