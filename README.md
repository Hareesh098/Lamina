\mainpage Lamina: A Molecular Dynamics Package

Welcome to the Lamina documentation!
# Lamina
========================================================================================================================
**Lamina** is a modular 2D molecular dynamics simulation package designed for simulating hybrid soft solids, including 
spring networks and finite-size discs. **Lamina** is a modular and extensible molecular dynamics (MD) simulation package 
written in C, designed to model a wide variety of soft and condensed matter systems. It supports time evolution using 
robust integrators and a range of thermostats, with accurate force evaluations for bonded and non-bonded interactions. 
Originally built for 2D simulations of bonded systems, **Lamina** has grown to support broader research goals including 
active matter, granular solids, and complex fluids.


# Why "Lamina"?
The word **Lamina** comes from Latin, meaning "a thin layer", "a plate", or "a sheet". In nature and science, laminae 
often refer to structural elements that are flat and extended in two dimensions for example, leaves, thin metal sheets, 
or tissue membranes.

This name reflects both the **two-dimensional** (2D) nature of the simulations and the types of materials **Lamina** is 
built to study; **liquids**, **soft solids**, and **networked structures** confined to thin sheets or layers. Just as 
natural laminae exhibit rich structural and dynamic behaviors in a seemingly simple geometry, this code is designed to 
explore the complexity of emergent phenomena in 2D materials and soft matter systems.


# Key Features
# Interaction Potentials
<pre>
Yukawa potential (screened Coulomb interactions)
Lennard-Jones potential (standard 12-6)
Harmonic bond potential (elastic network models)
Hookean granular contact potential (for soft granular matter)
</pre>

# Thermostats and Temperature Control
<pre>
Gaussian thermostat
Nose-Hoover thermostat
Langevin thermostat
Configurational temperature evaluation and control
</pre>

# Time Integration
<pre>
Leap-Frog integrator
Velocity-Verlet integrator
Langevin (stochastic) integrator
Brownian (overdamped) interator
</pre>

# Physical Observables
<pre>
Radial Distribution Function (RDF)
Velocity Autocorrelation Function (VACF)
Root-Mean-Square Velocity (VRMS)
Stress tensor and momentum
Center-of-mass motion
Space-time correlation functions
</pre>

# Output and Utilities
The output files are saved at the ../output folder. So you have a make a directory ../ location from where you are running the code.
<pre>
Command to run ./main prefix
Structured output files (`.xyz`, `.bond`, `.pair`, `.com`, `.result`)
Restart and resume capability (`.restart` and `.state` files)
Clean separation of source code, unit tests, and output
Support for Lees–Edwards boundary conditions (sheared systems)
Configurable halting conditions (based on VRMS or custom metric)
Modular design for easy extension of potentials and features
</pre>

# Project Structure
<pre>
Lamina/
  |- source/                # All C source files; avoid placing README.md here to prevent extra related pages
      |- main.c             # Main driver
      |- *.c, *.h           # Modular source files
  |- unittest/              # Unit test suite (planned or implemented)
      |- test_*.c           # Individual test cases
  |- output/                # All runtime output files will be saved here
  |- prepros/               # Preprocessing scripts or tools
      |- *.sh, *.py         # Example preprocessing scripts (shell, python, etc.)
  |- postpros/              # Postprocessing scripts or tools
      |- *.sh, *.py         # Example postprocessing scripts (shell, python, etc.)
  |- doxygen/               # Doxygen configuration and auxiliary files
      |- Doxyfile           # Doxygen config file
      |- header.tex         # Custom LaTeX header for documentation
      |- extra_stylesheet.css # Optional CSS to customize HTML output (e.g., hide Related Pages tab)
  |- figures/               # All figures, logos, icons used in docs and code
      |- LogoLaminaHTML.png # Project logo used in HTML and LaTeX docs
  |- docs/                  # Generated documentation output (HTML, LaTeX, PDFs)
      |- html/              # Doxygen-generated HTML documentation
      |- latex/             # Doxygen-generated LaTeX source files
      |- refman.pdf         # Generated PDF documentation (from LaTeX)
  |- Makefile               # Build system
  |- README.md              # Main project documentation (used as main page in Doxygen)
</pre>

# Documentation
- [Browse full HTML documentation](https://hareesh098.github.io/Lamina/)
- Download [Source code PDF manual](https://github.com/Hareesh098/Lamina/blob/main/docs/latex/refman.pdf)
- User manual [Physics PDF manual](https://github.com/Hareesh098/Lamina/blob/main/docs/README.pdf)
This documentation was generated using [Doxygen 1.10.0](https://www.doxygen.nl/) to ensure transparency and ease of review.

