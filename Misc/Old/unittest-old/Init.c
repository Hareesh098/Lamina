void Init() {
    char dummy[128];
    FILE *fpSTATE;

    // Open the input configuration file (STATE-Test)
    if ((fpSTATE = fopen("STATE-Test", "r")) == NULL) {
        printf("Error occurred: Could not open STATE file\n Exiting now..\n");
        exit(0);
    }

    // Read and parse data from STATE-Test
    fscanf(fpSTATE, "%s %lf", dummy, &timeNow);
    fscanf(fpSTATE, "%s %d",  dummy, &nAtom);
    fscanf(fpSTATE, "%s %d",  dummy, &nBond);
    fscanf(fpSTATE, "%s %d",  dummy, &nAtomType);
    fscanf(fpSTATE, "%s %d",  dummy, &nBondType);
    fscanf(fpSTATE, "%s %lf", dummy, &region[1]);
    fscanf(fpSTATE, "%s %lf", dummy, &region[2]);

    // Adjust region values
    region[2] *= 1.5; 

    // Calculate density and cell information
    density = nAtom / (region[1] * region[2]); 
    cells[1] = region[1] / rCut;
    cells[2] = region[2] / rCut;
    cellList = (int*)malloc((nAtom + cells[1] * cells[2] + 1) * sizeof(int));
    regionH[1] = 0.5 * region[1];
    regionH[2] = 0.5 * region[2];

    // Read atomic properties and bonds from STATE-Test
    rx = (double*)malloc((nAtom + 1) * sizeof(double));
    ry = (double*)malloc((nAtom + 1) * sizeof(double));
    vx = (double*)malloc((nAtom + 1) * sizeof(double));
    vy = (double*)malloc((nAtom + 1) * sizeof(double));
    ax = (double*)malloc((nAtom + 1) * sizeof(double));
    ay = (double*)malloc((nAtom + 1) * sizeof(double));
    atomID = (int*)malloc((nAtom + 1) * sizeof(int));
    atomType = (int*)malloc((nAtom + 1) * sizeof(int));
    atomRadius = (double*)malloc((nAtom + 1) * sizeof(double));

    // Initialize arrays to default values
    int n;
    for (n = 1; n <= nAtom; n++) {
        atomMass[n] = 1.0; // Default atomic mass
    }

    // Read atom data from STATE-Test
    fscanf(fpSTATE, "%s\n", dummy);
    for (n = 1; n <= nAtom; n++) {
        fscanf(fpSTATE, "%d %d %lf %lf %lf %lf %lf\n", &atomID[n], &atomType[n], &atomRadius[n], &rx[n], &ry[n], &vx[n], &vy[n]);
    }

    // Read bond data from STATE-Test
    fscanf(fpSTATE, "%s\n", dummy);
    for (n = 1; n <= nBond; n++) {
        fscanf(fpSTATE, "%d %d %d %d %lf %lf\n", &BondID[n], &BondType[n], &atom1[n], &atom2[n], &kb[n], &ro[n]);
    }

    fclose(fpSTATE);

    // List the interface atoms
    nAtomInterface = 0;  
    nAtomBlock = 0;
    for (n = 1; n <= nAtom; n++) {
        if (atomRadius[n] > 0.0) {
            nAtomInterface++; 
        }
        if (atomType[n] == 4 || atomType[n] == 5) {
            nAtomBlock++; 
        }
    }

    // Allocate memory for interface atoms
    atomIDInterface = (int*)malloc((nAtomInterface + 1) * sizeof(int));

    // Populate atomIDInterface array
    int m = 1;
    for (n = 1; n <= nAtom; n++) {
        if (atomRadius[n] > 0.0) {
            atomIDInterface[m] = atomID[n]; 
            m++; 
        }
    }

    // Output parameters (just an example)
    printf("nAtom: %d\n", nAtom);
    printf("nBond: %d\n", nBond);
    // More outputs as needed...
}

