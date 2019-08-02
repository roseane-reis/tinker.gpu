#ifndef TINKER_HOSTONLY

#  include "mod_pme.h"
#  include "util_rt.h"

TINKER_NAMESPACE_BEGIN
extern std::vector<FFTPlan>& fft_plans();

void fft_data(rc_op op) {
  if (op & rc_dealloc) {
    int idx = 0;
    while (idx < fft_plans().size()) {
      cufftDestroy(fft_plans()[idx]);
      ++idx;
    }
    fft_plans().clear();
  }

  if (op & rc_alloc) {
    assert(fft_plans().size() == 0);

    const size_t size = PMEUnit::all_objs().size();
    fft_plans().resize(size, FFTPlan());
  }

  if (op & rc_init) {
#  if defined(TINKER_SINGLE_PRECISION)
    const cufftType typ = CUFFT_C2C;
#  elif defined(TINKER_DOUBLE_PRECISION)
    const cufftType typ = CUFFT_Z2Z;
#  else
    static_assert(false, "");
#  endif

    int idx = 0;
    for (FFTPlan& iplan : fft_plans()) {
      auto& st = PMEUnit::all_objs()[idx];
      check_rt(cufftPlan3d(&iplan, st.nfft1, st.nfft2, st.nfft3, typ));
      ++idx;
    }
  }
}

void fftfront(PMEUnit pme_u) {
  FFTPlan iplan = fft_plans()[pme_u.unit()];
  auto& st = PMEUnit::all_objs()[pme_u.unit()];

#  if defined(TINKER_SINGLE_PRECISION)
  cufftExecC2C(iplan, reinterpret_cast<cufftComplex*>(st.qgrid),
               reinterpret_cast<cufftComplex*>(st.qgrid), CUFFT_FORWARD);
#  elif defined(TINKER_DOUBLE_PRECISION)
  cufftExecZ2Z(iplan, reinterpret_cast<cufftDoubleComplex*>(st.qgrid),
               reinterpret_cast<cufftDoubleComplex*>(st.qgrid), CUFFT_FORWARD);
#  else
  static_assert(false, "");
#  endif
}

void fftback(PMEUnit pme_u) {
  FFTPlan iplan = fft_plans()[pme_u.unit()];
  auto& st = PMEUnit::all_objs()[pme_u.unit()];

#  if defined(TINKER_SINGLE_PRECISION)
  cufftExecC2C(iplan, reinterpret_cast<cufftComplex*>(st.qgrid),
               reinterpret_cast<cufftComplex*>(st.qgrid), CUFFT_INVERSE);
#  elif defined(TINKER_DOUBLE_PRECISION)
  cufftExecZ2Z(iplan, reinterpret_cast<cufftDoubleComplex*>(st.qgrid),
               reinterpret_cast<cufftDoubleComplex*>(st.qgrid), CUFFT_INVERSE);
#  else
  static_assert(false, "");
#  endif
}
TINKER_NAMESPACE_END

#endif
