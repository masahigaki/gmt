.. index:: ! grdfft
.. include:: module_core_purpose.rst_

******
grdfft
******

|grdfft_purpose|

Synopsis
--------

.. include:: common_SYN_OPTs.rst_

**gmt grdfft** *ingrid* [ *ingrid2* ]
|-G|\ *outfile*\|\ *table*
[ |-A|\ *azimuth* ]
[ |-C|\ *zlevel* ]
[ |-D|\ [*scale*\|\ **g**] ]
[ |-E|\ [**r**\|\ **x**\|\ **y**][**+n**][**+w**\ [**k**]] ]
[ |-F|\ [**r**\|\ **x**\|\ **y**]\ *params* ]
[ |-I|\ [*scale*\|\ **g**] ]
[ |-M|\ *mgal_at_45* ]
[ |-N|\ *params* ]
[ |-Q|\ ]
[ |-S|\ *scale*\|\ **d** ]
[ |SYN_OPT-V| ]
[ |SYN_OPT-f| ]
[ |SYN_OPT--| ]

|No-spaces|

Description
-----------

**grdfft** will take the 2-D forward Fast Fourier Transform and perform
one or more mathematical operations in the frequency domain before
transforming back to the space domain. An option is provided to scale
the data before writing the new values to an output file. The horizontal
dimensions of the grid are assumed to be in meters. Geographical grids
may be used by specifying the |SYN_OPT-f| option that scales degrees to
meters. If you have grids with dimensions in km, you could change this
to meters using :doc:`grdedit` or scale the output with :doc:`grdmath`.

Required Arguments
------------------

.. |Add_ingrid| replace:: 2-D binary grid file to be operated on. For
    cross-spectral operations, also give the second grid file *ingrid2*.
.. include:: explain_grd_inout.rst_
    :start-after: ingrid-syntax-begins
    :end-before: ingrid-syntax-ends

**-G**\ *outfile*
    Specify the name of the output grid file (see :ref:`Grid File Formats
    <grd_inout_full>`) or the 1-D spectrum table (see |-E|).

Optional Arguments
------------------

.. _-A:

**-A**\ *azimuth*
    Take the directional derivative in the *azimuth* direction measured
    in degrees CW from north.

.. _-C:

**-C**\ *zlevel*
    Upward (for *zlevel* > 0) or downward (for *zlevel* < 0) continue
    the field *zlevel* meters.

.. _-D:

**-D**\ [*scale*\|\ **g**]
    Differentiate the field, i.e., take :math:`\frac{\partial}{\partial z}`
    of the grid *z*. This is equivalent
    to multiplying by :math:`k_r` in the frequency domain (:math:`k_r` is radial wave
    number). Append a scale to multiply by :math:`k_r \cdot`\ *scale*) instead.
    Alternatively, append **g** to indicate that your data are geoid
    heights in meters and output should be gravity anomalies in mGal. Repeatable.
    [Default is no scale].

.. _-E:

**-E**\ [**r**\|\ **x**\|\ **y**][**+n**][**+w**\ [**k**]]
    Estimate power spectrum in the radial or a horizontal direction. No grid file is created. If one grid
    is given then *f* (i.e., frequency or wave number), power[*f*],
    and 1 standard deviation in power[*f*] are written to the file set by
    |-G| [standard output]. If two grids are given we write *f* and 8 quantities:
    Xpower[*f*], Ypower[*f*], coherent power[*f*], noise power[*f*], phase[*f*],
    admittance[*f*], gain[*f*], coherency[*f*].  Each quantity is followed by
    its own 1-std dev error estimate, hence the output is 17 columns wide.
    Select your spectrum by choosing one of these directives:

    - **r** - Choose a radial spectrum [Default].
    - **x** - Compute the spectrum in the *x*-direction instead. 
    - **y** - Compute the spectrum in the *y*-direction instead. 
    
    Two modifiers are available the adjust the output further:

    - **+w** - Write wavelength *w* instead of frequency *f*, and if your grid
      is geographic you may further append **k** to scale wavelengths from
      meter [Default] to km.
    - **+n** - Normalize spectrum so that the mean spectral values per
      frequency are reported [By default the spectrum is obtained by summing
      over several frequencies.

.. _-F:

**-F**\ [**r**\|\ **x**\|\ **y**]\ *params*
    Filter the data. Place **x** or **y** immediately after |-F| to
    filter *x* or *y* direction only; default is isotropic [**r**].
    Choose between a cosine-tapered band-pass, a Gaussian band-pass
    filter, or a Butterworth band-pass filter.

    Cosine-taper:
        Specify four wavelengths *lc*/*lp*/*hp*/*hc* in correct units (see |SYN_OPT-f|)
        to design a bandpass filter: wavelengths greater than *lc* or less
        than *hc* will be cut, wavelengths greater than *lp* and less than
        *hp* will be passed, and wavelengths in between will be
        cosine-tapered. E.g., **-F**\ 1000000/250000/50000/10000 |SYN_OPT-f|
        will bandpass, cutting wavelengths > 1000 km and < 10 km, passing
        wavelengths between 250 km and 50 km. To make a highpass or lowpass
        filter, give hyphens (-) for *hp*/*hc* or *lc*/*lp*. E.g.,
        **-Fx**-/-/50/10 will lowpass *x*, passing wavelengths > 50 and
        rejecting wavelengths < 10. **-Fy**\ 1000/250/-/- will highpass *y*,
        passing wavelengths < 250 and rejecting wavelengths > 1000.
    Gaussian band-pass:
        Append *lo*/*hi*, the two wavelengths in correct units
        (see |SYN_OPT-f|) to design a bandpass filter. At the given wavelengths
        the Gaussian filter weights will be 0.5. To make a highpass or
        lowpass filter, give a hyphen (-) for the *hi* or *lo* wavelength,
        respectively. E.g., **-F**-/30 will lowpass the data using a
        Gaussian filter with half-weight at 30, while **-F**\ 400/- will
        highpass the data.
    Butterworth band-pass:
        Append *lo*/*hi*/*order*,
        the two wavelengths in correct units (see |SYN_OPT-f|) and the filter
        order (an integer) to design a bandpass filter. At the given cut-off
        wavelengths the Butterworth filter weights will be 0.707 (i.e., the
	power spectrum will therefore be reduced by 0.5). To make a
        highpass or lowpass filter, give a hyphen (-) for the *hi* or *lo*
        wavelength, respectively. E.g., **-F**-/30/2 will lowpass the data
        using a 2nd-order Butterworth filter, with half-weight at 30, while
        **-F**\ 400/-/2 will highpass the data.

    **Note**: For filtering in the time (or space) domain instead, see
    :doc:`grdfilter`.

.. _-G:

**-G**\ *outfile*\|\ *table*
    Filename for output netCDF grid file OR 1-D data table (see |-E|).
    This is optional for -E (spectrum written to standard output) but mandatory for
    all other options that require a grid output.

.. _-I:

**-I**\ [*scale*\|\ **g**]
    Integrate the field, i.e., compute :math:`\int z(x,y) dz`.
    This is equivalent to divide by :math:`k_r` in the frequency domain (:math:`k_r` is
    radial wave number). Append a scale to divide by :math:`k_r \cdot`\ *scale*
    instead. Alternatively, append **g** to indicate that your data set
    is gravity anomalies in mGal and output should be geoid heights in
    meters.  Repeatable. [Default is no scale].

.. _-M:

**-M**\ *mgal_at_45*
    Specify the value of the gravity in mili Gals at 45 degrees latitude (used to convert
    gravity anomalies to geoid heights). Default is 980619.9203 mGal (Moritz's 1980 IGF value).
    This value needs to be changed accordingly when using data from other planets.

.. _-N:

.. include:: explain_fft.rst_

.. _-Q:

**-Q**
    Selects no wavenumber operations. Useful in conjunction with |-N| modifiers
    when you wish to write out the 2-D spectrum (or other intermediate grid products)
    only.

.. _-S:

**-S**\ *scale*\|\ **d**
    Multiply each element by *scale* in the space domain (after the
    frequency domain operations). [Default is 1.0].  Alternatively,
    append **d** to convert deflection of vertical to micro-radians.

.. |Add_-V| replace:: |Add_-V_links|
.. include:: explain_-V.rst_
    :start-after: **Syntax**
    :end-before: **Description**

|SYN_OPT-f|
   Geographic grids (dimensions of longitude, latitude) will be converted to
   meters via a "Flat Earth" approximation using the current ellipsoid parameters.

.. include:: explain_help.rst_

Grid Distance Units
-------------------

If the grid does not have meter as the horizontal unit, append **+u**\ *unit* to the input file name to convert from the
specified unit to meter.  If your grid is geographic, convert distances to meters by supplying |SYN_OPT-f| instead.

Considerations
--------------

netCDF COARDS grids will automatically be recognized as geographic. For
other grids geographical grids were you want to convert degrees into
meters, select |SYN_OPT-f|. If the data are close to either pole, you should
consider projecting the grid file onto a rectangular coordinate system
using :doc:`grdproject`

Data Detrending
---------------

The default detrending mode is to remove a best-fitting linear plane (**+d**).
Consult and use |-N| to select other modes.

Normalization of Spectrum
-------------------------

By default, the power spectrum returned by |-E| simply sums the contributions
from frequencies that are part of the output frequency.  For *x*- or *y*-spectra
this means summing the power across the other frequency dimension, while for the
radial spectrum it means summing up power within each annulus of width *delta_q*,
the radial frequency (*q*) spacing.  A consequence of this summing is that the radial
spectrum of a white noise process will give a linear radial power spectrum that
is proportional to *q*.  Appending **n** will instead compute the mean power
per output frequency and in this case the white noise process will have a
white radial spectrum as well.

Examples
--------

.. include:: explain_example.rst_

To obtain the normalized radial spectrum from the remote data grid @white_noise.nc,
after removing the mean, let us try:

::

  gmt grdfft @white_noise.nc -Er+n -N+a > spectrum.txt

To upward continue the sea-level magnetic anomalies in the file
mag_0.nc to a level 800 m above sealevel:

::

  gmt grdfft mag_0.nc -C800 -V -Gmag_800.nc

To transform geoid heights in m (geoid.nc) on a geographical grid to
free-air gravity anomalies in mGal:

::

  gmt grdfft geoid.nc -Dg -V -Ggrav.nc

To transform gravity anomalies in mGal (faa.nc) to deflections of the
vertical (in micro-radians) in the 038 direction, we must first
integrate gravity to get geoid, then take the directional derivative,
and finally scale radians to micro-radians:

::

  gmt grdfft faa.nc -Ig -A38 -S1e6 -V -Gdefl_38.nc

Second vertical derivatives of gravity anomalies are related to the
curvature of the field. We can compute these as mGal/m\ :sup:`2` by:

::

  gmt grdfft gravity.nc -D -D -V -Ggrav_2nd_derivative.nc

To compute cross-spectral estimates for co-registered bathymetry and
gravity grids, and report result as functions of wavelengths in km, try:

::

  gmt grdfft bathymetry.nc gravity.grd -E+wk -fg -V > cross_spectra.txt

To examine the pre-FFT grid after detrending, point-symmetry reflection,
and tapering has been applied, as well as saving the real and imaginary
components of the raw spectrum of the data in topo.nc, try:

::

  gmt grdfft topo.nc -N+w+z -fg -V -Q

You can now make plots of the data in topo_taper.nc, topo_real.nc, and topo_imag.nc.

See Also
--------

:doc:`gmt`, :doc:`grdedit`,
:doc:`grdfilter`,
:doc:`grdmath`,
:doc:`grdproject`,
:doc:`gravfft <supplements/potential/gravfft>`
