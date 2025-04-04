#ifndef DELTA_H
#define DELTA_H

class Delta
{
public:
    Delta();
    Delta(double precedent, double actual);
    Delta(const Delta& other);

    double getPrecedent() const;
    double getActual() const;

    void setPrecedent(double value);
    void setActual(double value);

    double value() const;

    void update(double other);

private:
    double precedent;
    double actual;
};

#endif