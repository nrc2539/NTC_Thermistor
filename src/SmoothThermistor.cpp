/**
  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#include "SmoothThermistor.h"

SmoothThermistor::SmoothThermistor(
  Thermistor* origin,
  const int smoothingFactor
) {
  this->origin = origin;
  setSmoothingFactor(smoothingFactor);
}

SmoothThermistor::~SmoothThermistor() {
  delete this->origin;
}

double SmoothThermistor::readCelsius() {
  return this->celsius = smoothe(
    this->origin->readCelsius(),
    this->celsius
  );
}

double SmoothThermistor::readKelvin() {
  return this->kelvin = smoothe(
    this->origin->readKelvin(),
    this->kelvin
  );
}

double SmoothThermistor::readFahrenheit() {
  return this->fahrenheit = smoothe(
    this->origin->readFahrenheit(),
    this->fahrenheit
  );
}

inline double SmoothThermistor::smoothe(
  const double input,
  const double data
) {
  return (data == 0) ? input :
    ((data * (this->smoothingFactor - 1) + input) / this->smoothingFactor);
}

inline void SmoothThermistor::setSmoothingFactor(const int smoothingFactor) {
  this->smoothingFactor = (smoothingFactor > NTC_MIN_SMOOTHING_FACTOR) ?
    smoothingFactor :
    NTC_DEFAULT_SMOOTHING_FACTOR;
}
