// Nicolò Grilli
// Università di Bristol
// 29 Agosto 2024

#pragma once

#include "InitialCondition.h"
#include "DelimitedFileReader.h"

class InputParameters;

template <typename T>
InputParameters validParams();

/**
 * Defines a boundary condition that is read from file
 * and assigned to the nodes of a structured mesh
 */
class ReadFileIC : public InitialCondition
{
public:
  static InputParameters validParams();

  ReadFileIC(const InputParameters & parameters);
  
  /**
   * Read file and store data
   */
  virtual void getFileData();

protected:

  /**
   * The value of the variable at a point.
   */
  virtual Real value(const Point & p) override;

  /**
   * The value of the gradient at a point.
   */
  virtual RealGradient gradient(const Point & p) override;

  /// File should contain a single column with the value
  /// of the variable in each element of a structured mesh
  std::string _ic_file_name;
  
  /// Element size in the structured mesh
  /// size along x and y can be different
  const Real _element_size;
  const bool _different_xy_element_size;
  const Real _element_size_x;
  const Real _element_size_y;
  
  /// Number of elements along the x and y axes in the structured mesh
  const unsigned int _nx;
  const unsigned int _ny;

  /// Phase field index used to select the column in the file
  /// and total number of phase fields
  const unsigned int _op;
  const unsigned int _op_num;
  
  /// Data structure to store the information in the IC file
  std::vector<std::vector<Real>> _IC_data;
};
