#include <iostream>
#include <assert.h>
#include <string.h>
#include<vector>
using namespace std;


class AlertInterface
{
  public:
    virtual void raiseAlert(string patientName,const char* vitalName, const char* level) = 0;
};





class AlertWithSMS: public AlertInterface
{
  public:
    void raiseAlert(string patientName,const char* vitalName, const char* level) override
    {
      std::cout << "SMS: " <<patientName<<"--"<< vitalName << " " << level << std::endl;
    }
};




class AlertWithSound: public AlertInterface
{
  public:
    void raiseAlert(string patientName,const char* vitalName, const char* level) override
    {
      std::cout << "Sound: " <<patientName<<"--"<< vitalName << " " << level << std::endl;
    }
};




class VitalCheck
{
private:
    const char* Name;
    const char* PatientName;
    float Value;
    
    float UpperLimit;
    float LowerLimit;
    const char* Level;

    AlertInterface* Alert;

public:
    VitalCheck();
    VitalCheck(const char*, const char*, float, float, float, AlertInterface* alert);
    
    void CheckLevel();
    bool IsLevelOk();
};
VitalCheck::VitalCheck() : PatientName("0"),Value(0), UpperLimit(0), LowerLimit(0){}
VitalCheck::VitalCheck(const char* patientname, const char* name, float value, float lower_limit, float upper_limit, AlertInterface* alert) :
PatientName(patientname),Name(name), Value(value), LowerLimit(lower_limit), UpperLimit(upper_limit), Alert(alert)
{
    CheckLevel();
    IsLevelOk();
}
void VitalCheck::CheckLevel()
{
    if (Value < LowerLimit)
        Level = "LOW";
    else if (Value>UpperLimit)
        Level = "HIGH";
    else
        Level = "OK";
}
bool VitalCheck::IsLevelOk()
{
    if ( Level != "OK")
    {
        Alert->raiseAlert(PatientName,Name, Level);
        return false;
    }
    else
        return true;
}






class PatientVitals
{
private:
    VitalCheck bpm;
    VitalCheck spo2;
    VitalCheck respRate;
public:
    PatientVitals(const char* patientname,string age_group,float bpm, float spo2, float resprate, AlertInterface* alert);
};

PatientVitals::PatientVitals(const char* patientname,string age_group,float Bpm, float Spo2, float Resprate, AlertInterface* alert)
{
    if (age_group=="Adult")
    {
    VitalCheck bpm(patientname,"BPM", Bpm, 93, 157, alert);
    VitalCheck spo2(patientname,"SPO2", Spo2, 90, 100, alert);
    VitalCheck respRate(patientname,"RespRate",Resprate, 12, 25, alert);
    }
    else if (age_group=="Kid")
    {
        VitalCheck bpm(patientname,"BPM", Bpm, 88, 156, alert);
        VitalCheck spo2(patientname,"SPO2", Spo2, 90, 100, alert);
        VitalCheck respRate(patientname,"RespRate", Resprate, 21, 53, alert);
    }
    else if (age_group=="SeniorCitizen")
      {
          VitalCheck bpm(patientname,"BPM", Bpm, 80, 136, alert);
          VitalCheck spo2(patientname,"SPO2", Spo2, 90, 100, alert);
          VitalCheck respRate(patientname,"RespRate", Resprate, 12, 28, alert);
      }
    
    
}

int main()
{

   AlertInterface *alert_sms, *alert_sound;
   AlertWithSMS alert1;
   AlertWithSound alert2;
   alert_sms = &alert1;
   alert_sound = &alert2;

   PatientVitals("Rahul","Adult",60, 80, 20, alert_sms);
   PatientVitals("Eshaan","Kid",160, 180, 120, alert_sound);
   PatientVitals("Basheer","SeniorCitizen",80, 95, 25, alert_sms);
    
    
    
}

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
