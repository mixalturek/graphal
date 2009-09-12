#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  FILE * g;
  g = fopen("graph_3_2_3.txt","w");
  
  printf("graph started\n");  
  writeGraph(g, 3,2,3);
  printf("graph written\n");  
  fclose(g);       
  
  system("PAUSE");	
  return 0;
}


int writeGraph(FILE * g, int xsize, int ysize, int zsize){
  srand(123); // just some init
  
  int ix, iy, iz, id, id1, id2, iz1, iz2;   // indices of vertices
  double gt, gtt;                 // vertices and edges values
  
  int nvertices = xsize*ysize*zsize;
  int nedges = ((xsize-1)*ysize + xsize*(ysize-1))*zsize*zsize;
  int layersize = xsize*ysize; 
  int slabsize = xsize*zsize; // auxiliar 

  //g = fopen("graph.txt","w");
  // write is_oriented
  fprintf(g, "0\n\n");
  
  // write_number_of_vertices & number_of_edges
  fprintf(g, "%d %d \n\n", nvertices, nedges);
 
  // write_number_of_properties_for_vertices & names_of_properties_for_vertices
  fprintf(g, "4   __x __y __z  __gt\n");  // __gt is the value of the vertex
                                          // __x is the x coord of the vertex, etc.
  // write_number_of_properties_for_edges & names_of_properties_for_edges
  fprintf(g, "1   __gtt\n\n");  // __gtt is the value of the edge
  
  // for each vertex write vertex_id & values_of_properties
  id = 0;  
  for (iz = 0; iz < zsize; iz++)
    for (iy = 0; iy < ysize; iy++)
      for (ix = 0; ix < xsize; ix++) {
        gt = (double)rand()/(double)RAND_MAX;
        fprintf(g, "%d    %d  %d  %d    %0.4f\n", id, ix, iy, iz, gt);
        id++; // :-)
      } 
  fprintf(g, "\n"); //  separate vertically 
   
  // for each edge (= unordered pair of vertices) 
  // write vertex_id & write vertex_id & values_of_properties 
  // horizontal edges  
  for(iy = 0; iy < ysize; iy++)
    for (ix = 0; ix < xsize-1; ix++) {
      id1 = iy*xsize+ix;
      id2 = id1+1;  //eastern neighbour
      for (iz1 = 0; iz1 < zsize; iz1++)
        for (iz2 = 0; iz2 < zsize; iz2++){
          gtt = (double)rand()/(double)RAND_MAX;  
          fprintf(g, "%d  %d    %0.4f\n", id1+iz1*layersize, id2+iz2*layersize, gtt);  
        }    
    }

  //  vertical edges 
  for(iy = 0; iy < ysize-1; iy++)
    for (ix = 0; ix < xsize; ix++) {
      id1 = iy*xsize+ix;
      id2 = id1+xsize;    // southern neighbour
      for (iz1 = 0; iz1 < zsize; iz1++)
        for (iz2 = 0; iz2 < zsize; iz2++){
          gtt = (double)rand()/(double)RAND_MAX;  
          fprintf(g, "%d  %d    %0.4f\n", id1+iz1*layersize, id2+iz2*layersize, gtt);  
        }    
    }
return 0;
}
