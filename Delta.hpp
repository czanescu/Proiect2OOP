#ifndef DELTA_H
#define DELTA_H

class Delta
{
public:
    Delta();
    Delta(float precedent, float actual);
    Delta(const Delta& other);

    float getPrecedent() const;
    float getActual() const;
    float getAverage() const;

    void setPrecedent(float value);
    void setActual(float value);
    void setDelta(float precedent, float actual);

    float value() const;

    void update(float other);

    ~Delta() = default;

private:
    float m_precedent;
    float m_actual;
};

#endif