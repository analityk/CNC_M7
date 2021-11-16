#ifndef array_h__
#define array_h__

#include <asf.h>
#include <stdlib.h>

template < class T > class array{
	private:
	bool _full;
	bool _destroy;
	public:
	T* data;
	uint8_t capacity;
	uint8_t poz;

	array(uint8_t tsize){
		data = (T*)malloc(sizeof(T)*tsize);
		if( data == NULL){
			while(1){};
		};

		for(uint8_t r=0; r<tsize; r++){
			data[r] = T();
		};

		capacity = tsize;
		poz = 0;
		_full = false;
		_destroy = false;
	};

	~array(){
		poz = 0;
		capacity = 0;

		for(uint8_t volatile k=0; k<capacity; k++){
			data[k].T::~T();
		};
		free(data);
	};

	void destroy(void){
		if( _destroy )return;
		poz = 0;
		capacity = 0;
		free(data);
		_destroy = true;
	};

	uint8_t insert(T t){
		if( _destroy )return 2;
		if( poz == capacity ){ return 1; };
		data[poz] = t;
		poz++;
		return 0;
	};

	void erase(void){
		for(uint8_t i=0; i<capacity; i++){
			data[i] = 0;
		};
		poz = 0;
		_full = false;
	};

	T& read_last(void){
		if( !(_destroy) ){
			return data[poz-1];
		};
		return data[poz];
	};

	bool full(void){
		if( _destroy )return 0;
		if( free_space() == 0 ){
			return true;
		};
		return false;
	};

	uint8_t remove_last(void){
		if( _destroy )return 2;
		if( poz == 0 ){
			data[0].T::~T();
			return 1;
		};
		data[poz].T::~T();
		poz--;
		return 0;
	};

	uint8_t free_space(void){
		if( _destroy )return 0;
		return (capacity - poz);
	}

	uint8_t size(void){
		if( _destroy )return 0;
		return (capacity);
	};

	uint8_t cnts(void){
		return poz;
	};

	T& operator[] (uint8_t i)
	{
		if( _destroy )return (data[0]);
		if( (i >= 0) && (i <= capacity) ){
			return data[i];
		};
		return data[capacity-1];
	};
};

#endif // array_h__