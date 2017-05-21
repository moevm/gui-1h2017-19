#ifndef TABLE_H
#define TABLE_H


class Table
{
private:
    double const width;
    double const height;

public:
    Table(double width,
          double height);

    double getWidth() const;
    double getHeight() const;
};

#endif // TABLE_H
