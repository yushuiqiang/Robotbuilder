

#pragma warning (disable:4305 4244 4101 4761)
// SJR - I left this file as I received it, except for disabling the compiler warnings
// generated by it.


/******  FILE: invkin.p  ******/

/******************************************************************/
/**                                                              **/
/** PROGRAMMER:                                                  **/
/** DATE:        Nov 2, 1993                                     **/
/**                                                              **/
/** FUNCTION:    Inverse Kinematics -- compute the joint angles  **/
/**              (ANGLE) in pulse units for the MITSUBISHI       **/ 
/**              given the position and orientation of the end   **/
/**              effector (X).                                   **/
/**                                                              **/
/** USER GUIDE:  THE CALLING FORMAT IS:                          **/
/**              invkin(x,status,angle);                         **/
/**                                                              **/
/** VARIABLES :  STATUS = VALID_SOLUTION                         **/
/**                       REACH_EXCEEDED                         **/
/**                       LIMITS_EXCEEDED                        **/
/**                                                              **/
/** PROGRAMMER                                                   **/
/** GUIDE:       machine>  pc invkin.p -c                        **/
/**                      (This creates invkin.o)                 **/
/**                                                              **/
/** PROCEDURES                                                   **/
/** CALLED:          MATPRD                                      **/
/**                                                              **/
/** FUNCTIONS                                                    **/
/** CALLED:          ACTAN2                                      **/
/**                                                              **/
/** GLOBAL VARIABLES                                             **/
/** REFERENCED:      NONE                                        **/
/**                                                              **/
/******************************************************************/

#include "stdio.h"
#include "math.h"
#include "type_def.h"

float my_ACTAN2(Y, X)
float Y, X;
{
  float PI, SIGN;
  float temp;

    PI = 3.141592653589793;

    if (Y >= 0.0)
      SIGN = 1.0;
    else
      SIGN = - 1.0;
    if (abs(X) > 0.00001)  /* X IS NON-ZERO */
    {
      if (X > 0.0)
        temp=atan(Y/X);
      else
        temp=atan(Y / X) + PI * SIGN;
        /* END IF X */
    }
    else
       temp=PI / 2.0 * SIGN;
    return(temp);
}

float sqr(number)
float number;
{
  return(number*number);
}

void MATPRD(INMA, INMB, OUTM)
matx44 INMA, INMB, OUTM;
{
  matx44 WORKM; /* MATRIX USED TO HOLD PARTIAL ANSWER */
    /* UNTIL READY TO RETURN */
  int I, J, K;


    for (I=0; I < 4; I++)
      for (J=0; J < 4; J++)
        WORKM[I][J] = 0.0;
    for (I=0; I < 4; I++)
      for (J=0; J < 4; J++)
        for (K=0; K < 4; K++)
          WORKM[I][J] = INMA[I][K] * INMB[K][J] + WORKM[I][J];

    for (I =0; I < 4; I++)
      for (J = 0; J < 4; J++)
        OUTM[I][J] = WORKM[I][J];

}


void invkin(X, STATUS, ANG)
matx44 X;
enum STATUS_SET STATUS;
array6 ANG;
{
  float PI;
  int I, J, K;
  matx44 E, Z, TEMP, T5;
  float DUM, W, C1, S1, C3, S3, SEC3, R;
  float ANGLE[5];

    PI = 3.14159;
    /** SET UP THE E AND Z MATRIX **/

    for (I = 0; I < 4; I++) 
    {
      for (J=0; J < 4; J++)
      {
        E[I][J]=0.0;
        Z[I][J]=0.0;
      }
      E[I][I]=1.0;
      Z[I][I]=1.0;
    }
    E[2][3]=196.1;
    Z[2][3]=250.0;
    STATUS = VALID_SOLUTION;
    /** COMPUTE ELEMENTS OF T5 MATRIX **/

    /** INVERT E **/

    for (I=0; I < 4; I++)
       for (J=0; J < 4; J++)
          TEMP[I][J] = E[I][J];
    for (I=0; I < 3; I++)
      TEMP[I][3] = - TEMP[I][3];

    /** LET T5 = X x E INVERSE **/
    MATPRD(X, TEMP, T5);
    /** INVERT Z **/

    for (I=0; I < 4; I++)
       for (J=0; J < 4; J++) 
           TEMP[I][J] = Z[I][J];
 
    for (I=0; I < 3; I++)
      TEMP[I][3] = - TEMP[I][3];

    /** T5 = Z INVERSE x X x E INVERSE **/

    MATPRD(TEMP, T5, T5);
    /** COMPUTE JOINT ANGLES **/

      ANGLE[0] = atan2(T5[1][3],T5[0][3]);
      if ((ANGLE[0] >= - 2 * PI) &&
         (ANGLE[0] <= - 240.0 * PI / 180.0)) 
        ANGLE[0] = 2 * PI + ANGLE[0];
      if ((ANGLE[0] >= 240.0 * PI / 180.0) && (ANGLE[0] <= 2 * PI)) 
        ANGLE[0] = - 2 * PI + ANGLE[0];
      C1 = cos(ANGLE[0]);
      S1 = sin(ANGLE[0]);

      ANGLE[4] = atan2(((C1 * T5[1][0]) - (S1 * T5[0][0])),
                           ((C1 * T5[1][1]) - (S1 * T5[0][1])));


      R = C1*T5[0][3] + (S1*T5[1][3]);
      C3 = (sqr(R)+sqr(T5[2][3])-sqr(160.0)-sqr(220.0))/2.0/160.0/220.0;
      if (1 - sqr(C3) < 0) 
        STATUS = REACH_EXCEEDED;
      else
        ANGLE[2] = atan2(sqrt(1 - sqr(C3)), C3);

        if (ANGLE[2] < 0) 
          ANGLE[2] = - ANGLE[2];

      if ((ANGLE[2] >= - 2 * PI) &&
         (ANGLE[2] <= - 90.0 * PI / 180.0)) 
        ANGLE[2] = 2 * PI + ANGLE[2];
      if ((ANGLE[2] >= 180.0 * PI / 180.0) && (ANGLE[2] <= 2 * PI)) 
        ANGLE[2] = - 2 * PI + ANGLE[2];

      C3 = cos(ANGLE[2]);
      S3 = sin(ANGLE[2]);


        W = C1 * T5[0][3] + S1 * T5[1][3];
        ANGLE[1] =  atan2( - (160.0*C3 + 220.0) * T5[2][3]-160.0*S3*W,
                          ((160.0*C3 + 220.0) * W - 160.0*(S3 * T5[2][3])));
        if ((ANGLE[1] >= - 2 * PI) &&
            (ANGLE[1] <= - 330.0 * PI / 180.0)) 
          ANGLE[1] = 2 * PI + ANGLE[1];

        if ((ANGLE[1] >= 260.0 * PI / 180.0) && (ANGLE[1] <= 2 * PI)) 
          ANGLE[1] = - 2 * PI + ANGLE[1];


      ANGLE[3] = atan2(((C1 * T5[0][2]) + (S1 * T5[1][2])),
                    T5[2][2]) - ANGLE[1] - ANGLE[2];

      if ((ANGLE[3] > 180.0 * PI / 180.0) && (ANGLE[3] <= 2 * PI)) 
        ANGLE[3] = - 2 * PI + ANGLE[3];
      if ((ANGLE[3] >= - 2 * PI) &&
         (ANGLE[3] < - 180 * PI / 180.0)) 
        ANGLE[3] = 2 * PI + ANGLE[3];


    for (I=0; I < 5; I++)
      ANGLE[I] = ANGLE[I] * 180.0 / PI;
     

    if (STATUS == VALID_SOLUTION)
      if ((ANGLE[0] > 150) || (ANGLE[0] < - 150) || (ANGLE[1] > 30) ||
         (ANGLE[1] < - 100) || (ANGLE[2] > 90) ||
         (ANGLE[2] < - 0 ) || (ANGLE[3] > 180) ||
         (ANGLE[3] < - 0)) 
        STATUS = LIMITS_EXCEEDED;

 /** CONVERT D-H ANGLES INTO JOINT ANGLES **/

    ANGLE[0] = -(ANGLE[0]+150)*40;
    ANGLE[1] = -(ANGLE[1]+100)*40;
    ANGLE[2] = -(ANGLE[2]-90)*40;
    DUM = ANGLE[3];
    ANGLE[3] = -(ANGLE[3]+ANGLE[4]-180)*80/6;
    ANGLE[4] = (DUM-ANGLE[4]-180)*80/6;
    for (I=0; I < 5; I++)
      ANG[I]=ANGLE[I];
    ANG[5] = 0;
}



#pragma warning (default:4305 4244 4101 4761)


