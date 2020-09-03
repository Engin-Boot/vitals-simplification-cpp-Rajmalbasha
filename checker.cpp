#include <assert.h>
#include <iostream>

class AlertInterface
{
  public:
    virtual void raiseAlert(const char* vitalName, const char* level) = 0;
};

class AlertWithSMS: public AlertInterface
{
  public:
    void raiseAlert(const char* vitalName, const char* level) override
    {
      std::cout << "SMS: " << vitalName << " " << level << std::endl;
    }
};

class AlertWithSound: public AlertInterface
{
  public:
    void raiseAlert(const char* vitalName, const char* level) override
    {
      std::cout << "Sound: " << vitalName << " " << level << std::endl;  //'what'
    }
};

class AlertIntegrator : public AlertInterface
{
  private:
    AlertWithSMS smsAlerter;
    AlertWithSound soundAlerter;
  public:
    void raiseAlert(const char* vitalName, const char* level) override
    {
      smsAlerter.raiseAlert(vitalName, level);
      soundAlerter.raiseAlert(vitalName, level);
    }
};

class RangeChecker
{
  private:
    int lower;
    int upper;
    const char* vitalName;
    AlertInterface* alerter;
  public:
    RangeChecker(const char* name, int low, int up, AlertInterface* alerterPtr)
    {
      vitalName = name;
      lower = low;
      upper = up;
      alerter = alerterPtr;
    }
    void checkAgainstRange(float value)
    {
      if(value < lower) {
        alerter->raiseAlert(vitalName, "too low");  //'when'
      } else if(value > upper) {
        alerter->raiseAlert(vitalName, "too high");
      }
    }
};

class VitalsIntegrator
{
  private:
    RangeChecker bpmChecker, spo2Checker, respChecker;
  public:
    VitalsIntegrator(AlertInterface* alertPtr): 
      bpmChecker("pulse rate", 70, 150, alertPtr),
      spo2Checker("spo2", 90, 101, alertPtr),
      respChecker("resp rate", 30, 95, alertPtr)
    {}
    void checkAllVitals(float bpm, float spo2, float respRate)
    {
      bpmChecker.checkAgainstRange(bpm);
      spo2Checker.checkAgainstRange(spo2);
      respChecker.checkAgainstRange(respRate);
    }
};

int main() {
  AlertIntegrator alerter;  
  VitalsIntegrator vitals(&alerter);

  vitals.checkAllVitals(80, 95, 60);
  vitals.checkAllVitals(60, 90, 40);
}
