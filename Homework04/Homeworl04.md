## Part 1: Before running anything

1. It tells you the various frequencies component within the sampled signal
2. - the rate of witch your are measuring (sampling) your signal
    - The limit frequency you can sample without aliasing (and is garantied to be reconstructable). it is half the sampling rate
    - how finely you can distinguish two frequencies, the bins in your FFT alorithm
3. The FFT routine requires equal spacing to exploit regularities and take down the complexity to O(NlogN)

 ## Part 2: Build and run
 1. - `coupled_oscillators_spectrum.csv`
    - `coupled_oscillators_time.csv`
    - `good_sampling_signal.csv`
    - `good_sampling_spectrum.csv`
    - `short_record_signal.csv`
    - `short_record_spectrum.csv`
    - `undersampled_signal.csv`
    - `undersampled_spectrum.csv`

2. `sampling_demo` 
3. `coupled_oscillators_fft`

4. `    peak 1: f =   50.000 Hz, amplitude = 1.0000
    peak 2: f =  120.000 Hz, amplitude = 0.7000`

## Part 3: Sampling and aliasing
1. Yess
2. 64 Hz
3. Because it is above the Nyquist frequency, so aliasing will occur
4. Yess
5. Because the signal "sinusoid" is much faster than the sampling time and so for every time you sample multiple period has passed, and you just measure the extra progress modulus multiple periods. $f_{alias}$ follows $|f_sig-n*f_S|=|128-120|$ = 8 Hz



## Part 4: Frequency resolution
1. Yess
2. 64/512hz=0.125s
3. 512hz/64=8hz
4. Because the difference between the two frequencies is 5 Hz but our resolution is 8Hz
5. The problem is the frequency resolution, which depends solely on the acquisition time, so just a longer acquisition time save the plot

## Part 5: Coupled oscillators
1. $m \, \ddot{x}_1 = - (k + k_c) x_1 + k_c x_2$ and $m \, \ddot{x}_2 = k_c x_1 - (k + k_c) x_2$ with:
    - $m$ is the mass of each oscillator
    - $k$ is the spring constant of the wall springs
    - $k_c$ is the coupling spring constant
    - $x_1(t)$ and $x_2(t)$ are the two mass displacements
2. Two identical masses attached to walls with strings and coulpled between each others with another spring
3. In-phase and out-phase modes
4. With (non specific) initial conditions you end up exciting a combination of the normal modes
5. To check the modelling, numerical consistency and spot bugs in the code


## Part 6: Plot Inspection
1. `sampling_spetra.png -> Undersammpled line`
2. `sampling_spetra.png -> short-record line`
3. yess they do
4. it depends on both observation time(resolution) and discrete binning but also solver tollerance

## Part 7: Small code Modifications
Option A:
Aliasing case put down to 50 Hz, so the new aliased peak falls on $|120-2*50|$=20 Hz
```
  The 120 Hz component is above Nyquist for fs = 50 Hz and folds back to an alias near 20 Hz.
  sampling rate = 50.0 Hz, Nyquist = 25.0 Hz, duration = 2.560 s
  FFT frequency resolution = 0.391 Hz
  dominant spectral peaks:
    peak 1: f =   19.922 Hz, amplitude = 0.6532

```

## Part 8: Reflection
1. The aliasing Nyquist formula
2. I had never actually read the content of a make file
3. Study the binning dependance on the parameter of the FFT
