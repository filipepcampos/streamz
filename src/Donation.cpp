#include "Donation.h"

Donation::Donation(string s, unsigned int v, unsigned int e) : streamer(s), value(v), evaluation(e) {}

string Donation::getStreamer() const {
    return streamer;
}

unsigned Donation::getValue() const {
    return value;
}

unsigned Donation::getEvaluation() const {
    return evaluation;
}

bool Donation::operator<(const Donation &d) const {
    if (this->getValue() == d.getValue())
        return (this->getEvaluation() < d.getEvaluation());
    return this->getValue() < d.getValue();
}
