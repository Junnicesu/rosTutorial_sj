#ifndef carpark_h_
#define carpark_h_

namespace carparksrvc{

enum enumCarType {bicycle, car, bus};

class CarPark{
    public:
        static CarPark* GetInstance(){
            if(pSI==nullptr){
                pSI = new CarPark();
            }
            else{
                return pSI;
            }
        }
        bool ReqParking(enumCarType type){
            int* pNumLeft = getPnumVehicleParkleft(type);
            if(pNumLeft==nullptr) return false;
            if(*pNumLeft>0) { (*pNumLeft)--; return true; }
            else return false;
        }

        bool ReqLeaving(bool isPaid, enumCarType type){
            if(isPaid) {
                int* pNumLeft = getPnumVehicleParkleft(type);
                (*pNumLeft)++;
            }
            else{
                //sj todo, Please pay before leaving
            }
            return isPaid;
        }

    private:
        CarPark() :m_bicycleNum(30), m_carNum(100), m_busNum(15) {}      

        int* getPnumVehicleParkleft(enumCarType type){
            int* pNum = nullptr;
            switch (type)
            {
            case bicycle: pNum = &m_bicycleNum;
                break;
            case car: pNum = &m_carNum;
                break;
            case bus: pNum = &m_busNum;
                break;                            
            default:
                // error type input
                return nullptr;
            }
            return pNum;            
        }      

        int m_bicycleNum, m_carNum, m_busNum;
        static CarPark* pSI;
};

}

#endif