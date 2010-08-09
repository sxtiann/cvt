/*
 *  LevenbergMarquard.h
 *  VisionTools
 *
 *  Created by Sebastian Klose on 07.08.10.
 *  Copyright 2010. All rights reserved.
 *
 */
#ifndef TOOLS_LEVENBERG_MARQUARD_H
#define TOOLS_LEVENBERG_MARQUARD_H

#include <Eigen/Eigen>

class LevenbergMarquard
{
public:
	enum TerminationCriteria
	{
		Iterations,
		Epsilon,
		IterationsOrEpsilon
	};
	
	LevenbergMarquard(TerminationCriteria termCrit);
	
	void setMaxIterations(unsigned int maxIters);
	void setMaxEpsilon(double maxEps);
	
	virtual ~LevenbergMarquard();
	
	template <class CostFunctionType, class JacobianFunctionType>	
	void optimize(CostFunctionType& costs, 
				  JacobianFunctionType& jacFunc,
				  Eigen::VectorXd & start, 
				  Eigen::VectorXd& measurement,
				  Eigen::VectorXd & deltaParameters);
	
	bool checkTermination(unsigned int currIter, double currEpsilon);
	
private:
	unsigned int maxIterations;
	double maxEpsilon;	
	double lamda;
	const double lamdaUpdateFactor;
	
	TerminationCriteria terminationCriteria;
};

#endif

