      SUBROUTINE DQELG(N,EPSTAB,RESULT,ABSERR,RES3LA,NRES)
C***BEGIN PROLOGUE  DQELG
C***REFER TO  DQAGIE,DQAGOE,DQAGPE,DQAGSE
C***ROUTINES CALLED  D1MACH
C***REVISION DATE  830518   (YYMMDD)
C***KEYWORDS  EPSILON ALGORITHM, CONVERGENCE ACCELERATION,
C             EXTRAPOLATION
C***AUTHOR  PIESSENS,ROBERT,APPL. MATH. & PROGR. DIV. - K.U.LEUVEN
C           DE DONCKER,ELISE,APPL. MATH & PROGR. DIV. - K.U.LEUVEN
C***PURPOSE  THE ROUTINE DETERMINES THE LIMIT OF A GIVEN SEQUENCE OF
C            APPROXIMATIONS, BY MEANS OF THE EPSILON ALGORITHM OF
C            P.WYNN. AN ESTIMATE OF THE ABSOLUTE ERROR IS ALSO GIVEN.
C            THE CONDENSED EPSILON TABLE IS COMPUTED. ONLY THOSE
C            ELEMENTS NEEDED FOR THE COMPUTATION OF THE NEXT DIAGONAL
C            ARE PRESERVED.
C***DESCRIPTION
C
C           EPSILON ALGORITHM
C           STANDARD FORTRAN SUBROUTINE
C           DOUBLE PRECISION VERSION
C
C           PARAMETERS
C              N      - INTEGER
C                       EPSTAB(N) CONTAINS THE NEW ELEMENT IN THE
C                       FIRST COLUMN OF THE EPSILON TABLE.
C
C              EPSTAB - DOUBLE PRECISION
C                       VECTOR OF DIMENSION 52 CONTAINING THE ELEMENTS
C                       OF THE TWO LOWER DIAGONALS OF THE TRIANGULAR
C                       EPSILON TABLE. THE ELEMENTS ARE NUMBERED
C                       STARTING AT THE RIGHT-HAND CORNER OF THE
C                       TRIANGLE.
C
C              RESULT - DOUBLE PRECISION
C                       RESULTING APPROXIMATION TO THE INTEGRAL
C
C              ABSERR - DOUBLE PRECISION
C                       ESTIMATE OF THE ABSOLUTE ERROR COMPUTED FROM
C                       RESULT AND THE 3 PREVIOUS RESULTS
C
C              RES3LA - DOUBLE PRECISION
C                       VECTOR OF DIMENSION 3 CONTAINING THE LAST 3
C                       RESULTS
C
C              NRES   - INTEGER
C                       NUMBER OF CALLS TO THE ROUTINE
C                       (SHOULD BE ZERO AT FIRST CALL)
C
C***END PROLOGUE  DQELG
C
      DOUBLE PRECISION ABSERR,DABS,DELTA1,DELTA2,DELTA3,DMAX1,D1MACH,
     *  EPMACH,EPSINF,EPSTAB,ERROR,ERR1,ERR2,ERR3,E0,E1,E1ABS,E2,E3,
     *  OFLOW,RES,RESULT,RES3LA,SS,TOL1,TOL2,TOL3
      INTEGER I,IB,IB2,IE,INDX,K1,K2,K3,LIMEXP,N,NEWELM,NRES,NUM
      DIMENSION EPSTAB(52),RES3LA(3)
C
C           LIST OF MAJOR VARIABLES
C           -----------------------
C
C           E0     - THE 4 ELEMENTS ON WHICH THE COMPUTATION OF A NEW
C           E1       ELEMENT IN THE EPSILON TABLE IS BASED
C           E2
C           E3                 E0
C                        E3    E1    NEW
C                              E2
C           NEWELM - NUMBER OF ELEMENTS TO BE COMPUTED IN THE NEW
C                    DIAGONAL
C           ERROR  - ERROR = ABS(E1-E0)+ABS(E2-E1)+ABS(NEW-E2)
C           RESULT - THE ELEMENT IN THE NEW DIAGONAL WITH LEAST VALUE
C                    OF ERROR
C
C           MACHINE DEPENDENT CONSTANTS
C           ---------------------------
C
C           EPMACH IS THE LARGEST RELATIVE SPACING.
C           OFLOW IS THE LARGEST POSITIVE MAGNITUDE.
C           LIMEXP IS THE MAXIMUM NUMBER OF ELEMENTS THE EPSILON
C           TABLE CAN CONTAIN. IF THIS NUMBER IS REACHED, THE UPPER
C           DIAGONAL OF THE EPSILON TABLE IS DELETED.
C
C***FIRST EXECUTABLE STATEMENT  DQELG
      EPMACH = D1MACH(4)
      OFLOW = D1MACH(2)
      NRES = NRES+1
      ABSERR = OFLOW
      RESULT = EPSTAB(N)
      IF(N.LT.3) GO TO 100
      LIMEXP = 50
      EPSTAB(N+2) = EPSTAB(N)
      NEWELM = (N-1)/2
      EPSTAB(N) = OFLOW
      NUM = N
      K1 = N
      DO 40 I = 1,NEWELM
        K2 = K1-1
        K3 = K1-2
        RES = EPSTAB(K1+2)
        E0 = EPSTAB(K3)
        E1 = EPSTAB(K2)
        E2 = RES
        E1ABS = DABS(E1)
        DELTA2 = E2-E1
        ERR2 = DABS(DELTA2)
        TOL2 = DMAX1(DABS(E2),E1ABS)*EPMACH
        DELTA3 = E1-E0
        ERR3 = DABS(DELTA3)
        TOL3 = DMAX1(E1ABS,DABS(E0))*EPMACH
        IF(ERR2.GT.TOL2.OR.ERR3.GT.TOL3) GO TO 10
C
C           IF E0, E1 AND E2 ARE EQUAL TO WITHIN MACHINE
C           ACCURACY, CONVERGENCE IS ASSUMED.
C           RESULT = E2
C           ABSERR = ABS(E1-E0)+ABS(E2-E1)
C
        RESULT = RES
        ABSERR = ERR2+ERR3
C ***JUMP OUT OF DO-LOOP
        GO TO 100
   10   E3 = EPSTAB(K1)
        EPSTAB(K1) = E1
        DELTA1 = E1-E3
        ERR1 = DABS(DELTA1)
        TOL1 = DMAX1(E1ABS,DABS(E3))*EPMACH
C
C           IF TWO ELEMENTS ARE VERY CLOSE TO EACH OTHER, OMIT
C           A PART OF THE TABLE BY ADJUSTING THE VALUE OF N
C
        IF(ERR1.LE.TOL1.OR.ERR2.LE.TOL2.OR.ERR3.LE.TOL3) GO TO 20
        SS = 0.1D+01/DELTA1+0.1D+01/DELTA2-0.1D+01/DELTA3
        EPSINF = DABS(SS*E1)
C
C           TEST TO DETECT IRREGULAR BEHAVIOUR IN THE TABLE, AND
C           EVENTUALLY OMIT A PART OF THE TABLE ADJUSTING THE VALUE
C           OF N.
C
        IF(EPSINF.GT.0.1D-03) GO TO 30
   20   N = I+I-1
C ***JUMP OUT OF DO-LOOP
        GO TO 50
C
C           COMPUTE A NEW ELEMENT AND EVENTUALLY ADJUST
C           THE VALUE OF RESULT.
C
   30   RES = E1+0.1D+01/SS
        EPSTAB(K1) = RES
        K1 = K1-2
        ERROR = ERR2+DABS(RES-E2)+ERR3
        IF(ERROR.GT.ABSERR) GO TO 40
        ABSERR = ERROR
        RESULT = RES
   40 CONTINUE
C
C           SHIFT THE TABLE.
C
   50 IF(N.EQ.LIMEXP) N = 2*(LIMEXP/2)-1
      IB = 1
      IF((NUM/2)*2.EQ.NUM) IB = 2
      IE = NEWELM+1
      DO 60 I=1,IE
        IB2 = IB+2
        EPSTAB(IB) = EPSTAB(IB2)
        IB = IB2
   60 CONTINUE
      IF(NUM.EQ.N) GO TO 80
      INDX = NUM-N+1
      DO 70 I = 1,N
        EPSTAB(I)= EPSTAB(INDX)
        INDX = INDX+1
   70 CONTINUE
   80 IF(NRES.GE.4) GO TO 90
      RES3LA(NRES) = RESULT
      ABSERR = OFLOW
      GO TO 100
C
C           COMPUTE ERROR ESTIMATE
C
   90 ABSERR = DABS(RESULT-RES3LA(3))+DABS(RESULT-RES3LA(2))
     *  +DABS(RESULT-RES3LA(1))
      RES3LA(1) = RES3LA(2)
      RES3LA(2) = RES3LA(3)
      RES3LA(3) = RESULT
  100 ABSERR = DMAX1(ABSERR,0.5D+01*EPMACH*DABS(RESULT))
      RETURN
      END
