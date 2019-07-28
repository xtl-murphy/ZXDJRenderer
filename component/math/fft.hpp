//
// Created by murphy on 2019-07-04.
//

/**
 * fft
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-07-04 16:39
 **/
#ifndef ZXDJRENDERER_FFT_HPP
#define ZXDJRENDERER_FFT_HPP

#include <complex>

inline void transform(std::complex<double> *a, const int n, const std::complex<double> *omega)
{
    int k = 0;
    while ((1 << k) < n)
    {
        k++;
    }

}

#endif //ZXDJRENDERER_FFT_HPP
