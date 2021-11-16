//#ifndef array_h__
//#define array_h__
//
//#include <stdlib.h>
//
//#ifdef __cplusplus
//
//template <typename A, typename B>
//class Pair{
	//public:
	//A a;
	//B b;
	//
	//Pair():
	//a(0), b(0) {};
	//
	//Pair(A aa, B bb):
	//a(aa), b(bb) {};
	//
	//Pair(const Pair& p):
	//a(p.a), b(p.b) {};
//
//};
//
//template <typename A, const uint8_t S>
//class Array{
//public:
	//A* data;
	//uint8_t at;
	//uint8_t cnts;
		//
	//Array(){
		//data = (A*)malloc(sizeof(A) * S);
		//if(data != NULL){
			//for(uint8_t i=0; i<S; i++){
				//data[i] = A();
			//};
			//cnts = S;
			//at = 0;
		//};
	//};
	//
	//uint8_t operator[] (uint8_t t){
		//return data[t];
	//};
	//
	//A operator++(void){
		//at++;
		//if(at < cnts){
			//return data[at];
		//}else{
			//return data[cnts-1];
		//};
	//};
	//
	//A operator++(int){
		//at++;
		//if(at < cnts){
			//return data[at];
			//}else{
			//return data[cnts-1];
		//};
	//};
	//
	//uint8_t operator--(void){
		//if(at > 0){
			//at--;
			//return data[at];
		//}else{
			//return data[0];
		//}
	//};
	//
	//void clear(void){
		//for(uint8_t i=0; i<cnts; i++){
			//data[i].~A();
			//data[i] = 0;
		//};
		//at = 0;
	//};
	//
	//uint32_t allocated_memory(void){
		//return (sizeof(A) * cnts);
	//};
	//
//};
//
//
//#elif
//#error "cant find __cplusplus"
//#endif
//
//
//#endif // array_h__
