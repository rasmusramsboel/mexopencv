/**
 * @file getRectSubPix.cpp
 * @brief mex interface for cv::getRectSubPix
 * @ingroup imgproc
 * @author Kota Yamaguchi
 * @date 2012
 */
#include "mexopencv.hpp"
using namespace std;
using namespace cv;

/**
 * Main entry called from Matlab
 * @param nlhs number of left-hand-side arguments
 * @param plhs pointers to mxArrays in the left-hand-side
 * @param nrhs number of right-hand-side arguments
 * @param prhs pointers to mxArrays in the right-hand-side
 */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{
    // Check the number of arguments
    if (nrhs<3 || ((nrhs%2)!=1) || nlhs>1)
        mexErrMsgIdAndTxt("mexopencv:error","Wrong number of arguments");

    // Argument vector
    vector<MxArray> rhs(prhs,prhs+nrhs);

    // Option processing
    int patchType = -1;
    for (int i=3; i<nrhs; i+=2) {
        string key = rhs[i].toString();
        if (key=="PatchType")
            patchType = rhs[i+1].toInt();
        else
            mexErrMsgIdAndTxt("mexopencv:error","Unrecognized option");
    }

    // Process
    Mat image(rhs[0].toMat()), dst;
    Size patchSize = rhs[1].toSize();
    Point2f center = rhs[2].toPoint_<float>();
    getRectSubPix(image, patchSize, center, dst, patchType);
    plhs[0] = MxArray(dst);
}
