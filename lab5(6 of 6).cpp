#include<iostream>
#include <assert.h>
using namespace std;
int people_on_base;
int vehicles_on_base; 
double petrol_on_base; 
double goods_on_base;


class Vehicle {

public:double TANK_VOLUME;
double PETROL_AMOUNT ;
	Vehicle(){}
	Vehicle(double petrol_amount,double tank_volume)
	{
		PETROL_AMOUNT=petrol_amount;
		TANK_VOLUME=tank_volume;
	}
	double getTankVolume() const{return TANK_VOLUME;}
	double getPetrolAmount() const {return PETROL_AMOUNT;}

	void arrive()
	{
		people_on_base++;
		vehicles_on_base++;
	}
	int leave(){
		if(vehicles_on_base>0&&people_on_base>0&&petrol_on_base>=PETROL_AMOUNT){
		vehicles_on_base --;
		people_on_base --;
		petrol_on_base =petrol_on_base-(TANK_VOLUME-PETROL_AMOUNT);
		PETROL_AMOUNT=TANK_VOLUME;//polni' BAK bensina
		return 0;
		}
		else return -1;
		
		
	// ------ залить полный бак и покинуть базу; в случае невозможности уехать возвращает -1;

	}
};
class Bus:public Vehicle{
int PEOPLE,MAX_PEOPLE;double PETROL,MAX_PETROL;
public:
	
	Bus(int people, int max_people, double petrol, double max_petrol)//max-people количество пасажирск мест
	   {
		   PEOPLE=people;
		   MAX_PEOPLE=max_people;
		   PETROL=petrol;
		   MAX_PETROL=max_petrol;
	 
	   }
int getPeopleCount() const{return PEOPLE;}
int getMaxPeople() const{return MAX_PEOPLE;}

double getTankVolume() {TANK_VOLUME=MAX_PETROL;return TANK_VOLUME;}
double getPetrolAmount() {PETROL_AMOUNT=PETROL;return PETROL_AMOUNT;}
void arrive()
{people_on_base=people_on_base+PEOPLE;
		people_on_base++;//+1 voditel
		vehicles_on_base++;
		PEOPLE=0;
}
int leave()
{
	if(vehicles_on_base>0&&petrol_on_base>=PETROL&&people_on_base>0){

		vehicles_on_base --;
		people_on_base--;//-1 voditel
		people_on_base=people_on_base-MAX_PEOPLE;
		if(people_on_base<=MAX_PEOPLE){people_on_base=people_on_base-people_on_base;}
		
		
		petrol_on_base =petrol_on_base-(MAX_PETROL-PETROL);
		PETROL=MAX_PETROL;//polni' BAK bensina
		PEOPLE=MAX_PEOPLE;
		
		return 0;// ------ залить полный бак и покинуть базу; в случае невозможности уехать возвращает -1;
	}else return-1;

	}

};
class Truck:public Vehicle{
double LOAD,MAX_LOAD;double PETROL,MAX_PETROL;
public:
	Truck(double load, double max_load, double petrol, double max_petrol){
	LOAD=load;
	MAX_LOAD=max_load;
	PETROL=petrol;
	MAX_PETROL=max_petrol;
	}
	double getCurrentLoad() const{return LOAD;}
	double getMaxLoad() const{return MAX_LOAD;}
	double getTankVolume() {TANK_VOLUME=MAX_PETROL;return TANK_VOLUME;}
	double getPetrolAmount()  {PETROL_AMOUNT=PETROL;return PETROL_AMOUNT;}
	void arrive()
	{
			goods_on_base=goods_on_base+LOAD;
			people_on_base++;
			vehicles_on_base++;
			LOAD=0;
	}

	int leave()
	{	if(vehicles_on_base>0&&petrol_on_base>=PETROL&&people_on_base>0){
		vehicles_on_base--;
		people_on_base--;
		petrol_on_base =petrol_on_base-(MAX_PETROL-PETROL);
		goods_on_base=goods_on_base-MAX_LOAD;
		PETROL=MAX_PETROL;//polni' BAK bensina
		LOAD=MAX_LOAD;
		
		return 0;
	}else return-1;

	}
};
int main()
{
// ctor
Truck v(3.5, 4.0, 19.5, 60);

// get
assert(v.getCurrentLoad() == 3.5);
assert(v.getMaxLoad() == 4.0);
assert(v.getPetrolAmount() == 19.5);
assert(v.getTankVolume() == 60);

// ctor exact
Truck v_exact(4.0, 4.0, 60, 60);
assert(v_exact.getCurrentLoad() == 4.0);
assert(v_exact.getPetrolAmount() == 60);
v_exact.arrive();
v_exact.leave();

petrol_on_base = 1051;		// liters
people_on_base = 84;		// count
goods_on_base  = 5.032;		// tons
vehicles_on_base = 49;

// arrive
v.arrive();

assert(v.getPetrolAmount() == 19.5);	// same
assert(v.getTankVolume() == 60);

assert(v.getCurrentLoad() == 0);		// arrived
assert(v.getMaxLoad() == 4.0);

assert(vehicles_on_base == 50);
assert(people_on_base == 85);
assert(goods_on_base == 5.032+3.5);

assert(petrol_on_base == 1051);			// same

// leave
assert(v.leave() >= 0);

assert(v.getPetrolAmount() == 60);
assert(v.getTankVolume() == 60);
assert(v.getCurrentLoad()==v.getMaxLoad());

assert(vehicles_on_base == 49);					// leaved
assert(people_on_base == 84);
assert(petrol_on_base == 1051-(60-19.5));
assert(goods_on_base == 5.032 + 3.5 - 4.0);

////////// not enough petrol ////////////
Truck v2(3.5, 4.0, 50, 100);
petrol_on_base = 40;
goods_on_base = 5.032;
v2.arrive();
assert(v2.leave() < 0);

// all the same
assert(vehicles_on_base == 50);
assert(people_on_base == 85);
assert(petrol_on_base == 40);
assert(goods_on_base == 5.032+3.5);

//////// exactly petrol //////////
petrol_on_base = 50;
people_on_base = 101;	// 100 + driver
assert(v2.leave() >= 0);

// leaved
assert(vehicles_on_base == 49);
assert(people_on_base == 100);
assert(petrol_on_base == 0);
assert(goods_on_base == 5.032 + 3.5 - 4.0);

cout << "OK\n";

}