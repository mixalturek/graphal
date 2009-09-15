#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int writeGraph(int xsize, int ysize, int zsize);

int main(int argc, char *argv[])
{
	if(argc < 4)
	{
		fprintf(stderr, "Usage: %s <xsize> <ysize> <zsize>\n", argv[0]);
		return 1;
	}

	srand(time(NULL));

	writeGraph(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	return 0;
}


int writeGraph(int xsize, int ysize, int zsize)
{
	int ix, iy, iz, id, id1, id2, iz1, iz2;   // indices of vertices
	double gt, gtt;                 // vertices and edges values

	int nvertices = xsize*ysize*zsize;
	int nedges = ((xsize-1)*ysize + xsize*(ysize-1))*zsize*zsize;
	int layersize = xsize*ysize;

	int xmax = (xsize % 2 == 0) ? xsize/2 : xsize/2 + 1;
	int ymax = (ysize % 2 == 0) ? ysize/2 : ysize/2 + 1;
	int zmax = (zsize % 2 == 0) ? zsize/2 : zsize/2 + 1;

	// write is_oriented
	printf("0\n\n");

	// write_number_of_vertices & number_of_edges
	printf("%d %d \n\n", nvertices, nedges);

	// write_number_of_properties_for_vertices & names_of_properties_for_vertices
	printf("4\t__x __y __z __w\n");  // __gt is the value of the vertex
						// __x is the x coord of the vertex, etc.
	// write_number_of_properties_for_edges & names_of_properties_for_edges
	printf("1\t__w\n\n");  // __gtt is the value of the edge

	// for each vertex write vertex_id & values_of_properties
	id = 0;
	for (iz = -zsize/2; iz < zmax; iz++)
	{
		for (iy = -ysize/2; iy < ymax; iy++)
		{
			for (ix = -xsize/2; ix < xmax; ix++)
			{
				gt = (double)rand()/(double)RAND_MAX;
				printf("%d\t%d %d %d\t%0.4f\n", id, ix, iy, iz, gt);
				id++; // :-)
			}
		}
	}

	printf("\n"); //  separate vertically

	// for each edge (= unordered pair of vertices)
	// write vertex_id & write vertex_id & values_of_properties
	// horizontal edges
	for(iy = 0; iy < ysize; iy++)
	{
		for (ix = 0; ix < xsize-1; ix++)
		{
			id1 = iy*xsize+ix;
			id2 = id1+1;  //eastern neighbour
			for (iz1 = 0; iz1 < zsize; iz1++)
			{
				for (iz2 = 0; iz2 < zsize; iz2++)
				{
					gtt = (double)rand()/(double)RAND_MAX;
					printf("%d %d\t%0.4f\n", id1+iz1*layersize, id2+iz2*layersize, gtt);
				}
			}
		}
	}

	//  vertical edges
	for(iy = 0; iy < ysize-1; iy++)
	{
		for (ix = 0; ix < xsize; ix++)
		{
			id1 = iy*xsize+ix;
			id2 = id1+xsize;    // southern neighbour
			for (iz1 = 0; iz1 < zsize; iz1++)
			{
				for (iz2 = 0; iz2 < zsize; iz2++)
				{
					gtt = (double)rand()/(double)RAND_MAX;
					printf("%d %d\t%0.4f\n", id1+iz1*layersize, id2+iz2*layersize, gtt);
				}
			}
		}
	}

	return 0;
}
