#include <tracker.h>

void Tracker::line_3d(Vector* start, Vector* stop)
{
	int32_t dx = abs(stop->x - start->x);
    int32_t dy = abs(stop->y - start->y);
    int32_t dz = abs(stop->z - start->z);
	int8_t xs = 0;
	int8_t ys = 0;
	int8_t zs = 0;

    if(stop->x > start->x){
		xs = 1;
	}else{
		xs = -1;
	};

    if(stop->y > start->y){
        ys = 1;
	}else{
		ys = -1;
	};

	if(stop->z > start->z){
        zs = 1;
    }else{
        zs = -1;
	};

    //Driving axis is X-axis"
    if(dx >= dy && dx >= dz){
        int32_t p1 = 2 * dy - dx;
        int32_t p2 = 2 * dz - dx;

		while(start->x != stop->x){
            start->x += xs;
            if(p1 >= 0){
                start->y += ys;
                p1 -= 2 * dx;
			};
            if(p2 >= 0){
                start->z += zs;
                p2 -= 2 * dx;
			};
            p1 += 2 * dy;
            p2 += 2 * dz;
            // tracker.step(x,y,z);
		};
	}else{
		if(dy >= dx && dy >= dz){
			int32_t p1 = 2 * dx - dy;
			int32_t p2 = 2 * dz - dy;

			while(start->y != stop->y){
				start->y += ys;
				if(p1 >= 0){
					start->x += xs;
					p1 -= 2 * dy;
				};
				if(p2 >= 0){
					start->z += zs;
					p2 -= 2 * dy;
				};
				p1 += 2 * dx;
				p2 += 2 * dz;
				// tracker.step(x,y,z);
			};
		}else{
			int32_t p1 = 2 * dy - dz;
			int32_t p2 = 2 * dx - dz;

			while(start->z != stop->z){
				start->z += zs;
				if(p1 >= 0){
					start->y += ys;
					p1 -= 2 * dz;
				};
				if(p2 >= 0){
					start->x += xs;
					p2 -= 2 * dz;
				};
				p1 += 2 * dy;
				p2 += 2 * dx;
				// tracker.step(x,y,z);
			};
		};

	};
};

void Tracker::step(int8_t x, int8_t y, int8_t z)
{

}
