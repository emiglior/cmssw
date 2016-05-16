#ifndef RecoLocalTracker_Phase2PixelClusterizer_Phase2PixelArrayBuffer_H
#define RecoLocalTracker_Phase2PixelClusterizer_Phase2PixelArrayBuffer_H

//----------------------------------------------------------------------------
//! \class Phase2PixelArrayBuffer
//! \brief Class to store ADC counts during clustering.
//!
//! This class defines the buffer where the pixel ADC are stored.
//! The size is the number of rows and cols into a
//! ROC and it is set in the PhasePixelThresholdClusterizer
//!
//! TO DO: the chip size should be obtained in some better way.
//!
//! History:
//!    Modify the indexing to col*nrows + row. 9/01 d.k.
//!    Add setSize method to adjust array size. 3/02 d.k.
//----------------------------------------------------------------------------

// We use PixelPos which is an inner class of Phase2PixelCluster:
#include "DataFormats/Phase2PixelCluster/interface/Phase2PixelCluster.h"

#include <vector>
#include <iostream>



class Phase2PixelArrayBuffer 
{
 public:
  inline Phase2PixelArrayBuffer( int rows, int cols);
  inline Phase2PixelArrayBuffer( ){}
  
  inline void setSize( int rows, int cols);
  inline int operator()( int row, int col) const;
  inline int operator()( const Phase2PixelCluster::PixelPos&) const;
  inline int rows() const { return nrows;}
  inline int columns() const { return ncols;}

  inline bool inside(int row, int col) const;
  inline void set_adc( int row, int col, int adc);
  inline void set_adc( const Phase2PixelCluster::PixelPos&, int adc);
  int size() const { return pixel_vec.size();}

  /// Definition of indexing within the buffer.
  int index( int row, int col) const {return col*nrows+row;}
  int index( const Phase2PixelCluster::PixelPos& pix) const { return index(pix.row(), pix.col()); }

 private:
  std::vector<int> pixel_vec;   // TO DO: any benefit in using shorts instead?
  int nrows;
  int ncols;
};



Phase2PixelArrayBuffer::Phase2PixelArrayBuffer( int rows, int cols) 
  : pixel_vec(rows*cols,0),  nrows(rows), ncols(cols) {}


void Phase2PixelArrayBuffer::setSize( int rows, int cols) {
  pixel_vec.resize(rows*cols,0);
  nrows = rows;
  ncols = cols;
}


bool Phase2PixelArrayBuffer::inside(int row, int col) const 
{
  return ( row >= 0 && row < nrows && col >= 0 && col < ncols);
}


int Phase2PixelArrayBuffer::operator()(int row, int col) const  { return pixel_vec[index(row,col)];}


int Phase2PixelArrayBuffer::operator()(const Phase2PixelCluster::PixelPos& pix) const {return pixel_vec[index(pix)];}

// unchecked!
void Phase2PixelArrayBuffer::set_adc( int row, int col, int adc) 
{
  pixel_vec[index(row,col)] = adc;
}


void Phase2PixelArrayBuffer::set_adc( const Phase2PixelCluster::PixelPos& pix, int adc)
{
  pixel_vec[index(pix)] = adc;
}


#endif
