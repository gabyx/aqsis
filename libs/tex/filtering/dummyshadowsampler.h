// Aqsis
// Copyright (C) 2001, Paul C. Gregory and the other authors and contributors
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of the software's owners nor the names of its
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// (This is the New BSD license)

/** \file
 *
 * \brief Dummy shadow sampler for missing files
 *
 * \author Chris Foster [ chris42f (at) gmail (dot) com ]
 */

#ifndef DUMMYSHADOWSAMPLER_H_INCLUDED
#define DUMMYSHADOWSAMPLER_H_INCLUDED

#include <aqsis/tex/filtering/ishadowsampler.h>

namespace Aqsis {

/** \brief Placeholder shadow sampler implementation
 *
 * Dummy sampler to be used in place of a real one when the requested file is
 * not found.
 */
class AQSIS_TEX_SHARE CqDummyShadowSampler : public IqShadowSampler
{
	public:
		/// Return not-in-shadow always.
		virtual void sample(const Sq3DSampleQuad& sampleQuad,
				const CqShadowSampleOptions& sampleOpts, TqFloat* outSamps) const;
};


//==============================================================================
// Implementation details.
//==============================================================================

inline void CqDummyShadowSampler::sample(const Sq3DSampleQuad& sampleQuad,
		const CqShadowSampleOptions& sampleOpts, TqFloat* outSamps) const
{
	outSamps[0] = 0;
}

} // namespace Aqsis

#endif // DUMMYSHADOWSAMPLER_H_INCLUDED
