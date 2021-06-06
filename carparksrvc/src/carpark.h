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
            int* pNumLeft;
            switch (type)
            {
            case bicycle: pNumLeft = &m_bicycleNum;
                break;
            case car: pNumLeft = &m_carNum;
                break;
            case bus: pNumLeft = &m_busNum;
                break;                            
            default:
                // error type input
                return false;
            }
            if(*pNumLeft>0) { (*pNumLeft)--; return true; }
            else return false;
        }
    private:
        CarPark() :m_bicycleNum(30), m_carNum(100), m_busNum(15) {}            
        int m_bicycleNum, m_carNum, m_busNum;
        static CarPark* pSI;
};

}

#endif