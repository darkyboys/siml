/*
Creative Commons Legal Code

CC0 1.0 Universal

    CREATIVE COMMONS CORPORATION IS NOT A LAW FIRM AND DOES NOT PROVIDE
    LEGAL SERVICES. DISTRIBUTION OF THIS DOCUMENT DOES NOT CREATE AN
    ATTORNEY-CLIENT RELATIONSHIP. CREATIVE COMMONS PROVIDES THIS
    INFORMATION ON AN "AS-IS" BASIS. CREATIVE COMMONS MAKES NO WARRANTIES
    REGARDING THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS
    PROVIDED HEREUNDER, AND DISCLAIMS LIABILITY FOR DAMAGES RESULTING FROM
    THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS PROVIDED
    HEREUNDER.

Statement of Purpose

The laws of most jurisdictions throughout the world automatically confer
exclusive Copyright and Related Rights (defined below) upon the creator
and subsequent owner(s) (each and all, an "owner") of an original work of
authorship and/or a database (each, a "Work").

Certain owners wish to permanently relinquish those rights to a Work for
the purpose of contributing to a commons of creative, cultural and
scientific works ("Commons") that the public can reliably and without fear
of later claims of infringement build upon, modify, incorporate in other
works, reuse and redistribute as freely as possible in any form whatsoever
and for any purposes, including without limitation commercial purposes.
These owners may contribute to the Commons to promote the ideal of a free
culture and the further production of creative, cultural and scientific
works, or to gain reputation or greater distribution for their Work in
part through the use and efforts of others.

For these and/or other purposes and motivations, and without any
expectation of additional consideration or compensation, the person
associating CC0 with a Work (the "Affirmer"), to the extent that he or she
is an owner of Copyright and Related Rights in the Work, voluntarily
elects to apply CC0 to the Work and publicly distribute the Work under its
terms, with knowledge of his or her Copyright and Related Rights in the
Work and the meaning and intended legal effect of CC0 on those rights.

1. Copyright and Related Rights. A Work made available under CC0 may be
protected by copyright and related or neighboring rights ("Copyright and
Related Rights"). Copyright and Related Rights include, but are not
limited to, the following:

  i. the right to reproduce, adapt, distribute, perform, display,
     communicate, and translate a Work;
 ii. moral rights retained by the original author(s) and/or performer(s);
iii. publicity and privacy rights pertaining to a person's image or
     likeness depicted in a Work;
 iv. rights protecting against unfair competition in regards to a Work,
     subject to the limitations in paragraph 4(a), below;
  v. rights protecting the extraction, dissemination, use and reuse of data
     in a Work;
 vi. database rights (such as those arising under Directive 96/9/EC of the
     European Parliament and of the Council of 11 March 1996 on the legal
     protection of databases, and under any national implementation
     thereof, including any amended or successor version of such
     directive); and
vii. other similar, equivalent or corresponding rights throughout the
     world based on applicable law or treaty, and any national
     implementations thereof.

2. Waiver. To the greatest extent permitted by, but not in contravention
of, applicable law, Affirmer hereby overtly, fully, permanently,
irrevocably and unconditionally waives, abandons, and surrenders all of
Affirmer's Copyright and Related Rights and associated claims and causes
of action, whether now known or unknown (including existing as well as
future claims and causes of action), in the Work (i) in all territories
worldwide, (ii) for the maximum duration provided by applicable law or
treaty (including future time extensions), (iii) in any current or future
medium and for any number of copies, and (iv) for any purpose whatsoever,
including without limitation commercial, advertising or promotional
purposes (the "Waiver"). Affirmer makes the Waiver for the benefit of each
member of the public at large and to the detriment of Affirmer's heirs and
successors, fully intending that such Waiver shall not be subject to
revocation, rescission, cancellation, termination, or any other legal or
equitable action to disrupt the quiet enjoyment of the Work by the public
as contemplated by Affirmer's express Statement of Purpose.

3. Public License Fallback. Should any part of the Waiver for any reason
be judged legally invalid or ineffective under applicable law, then the
Waiver shall be preserved to the maximum extent permitted taking into
account Affirmer's express Statement of Purpose. In addition, to the
extent the Waiver is so judged Affirmer hereby grants to each affected
person a royalty-free, non transferable, non sublicensable, non exclusive,
irrevocable and unconditional license to exercise Affirmer's Copyright and
Related Rights in the Work (i) in all territories worldwide, (ii) for the
maximum duration provided by applicable law or treaty (including future
time extensions), (iii) in any current or future medium and for any number
of copies, and (iv) for any purpose whatsoever, including without
limitation commercial, advertising or promotional purposes (the
"License"). The License shall be deemed effective as of the date CC0 was
applied by Affirmer to the Work. Should any part of the License for any
reason be judged legally invalid or ineffective under applicable law, such
partial invalidity or ineffectiveness shall not invalidate the remainder
of the License, and in such case Affirmer hereby affirms that he or she
will not (i) exercise any of his or her remaining Copyright and Related
Rights in the Work or (ii) assert any associated claims and causes of
action with respect to the Work, in either case contrary to Affirmer's
express Statement of Purpose.

4. Limitations and Disclaimers.

 a. No trademark or patent rights held by Affirmer are waived, abandoned,
    surrendered, licensed or otherwise affected by this document.
 b. Affirmer offers the Work as-is and makes no representations or
    warranties of any kind concerning the Work, express, implied,
    statutory or otherwise, including without limitation warranties of
    title, merchantability, fitness for a particular purpose, non
    infringement, or the absence of latent or other defects, accuracy, or
    the present or absence of errors, whether or not discoverable, all to
    the greatest extent permissible under applicable law.
 c. Affirmer disclaims responsibility for clearing rights of other persons
    that may apply to the Work or any use thereof, including without
    limitation any person's Copyright and Related Rights in the Work.
    Further, Affirmer disclaims responsibility for obtaining any necessary
    consents, permissions or other rights required for any use of the
    Work.
 d. Affirmer understands and acknowledges that Creative Commons is not a
    party to this document and has no duty or obligation with respect to
    this CC0 or use of the Work.

*/

// SIML - Simple Image Manipulation Library for C++
// Founded by Tanishq pal on Sep 21 2026 at 03:34PM IST
// A Library specifically made to be fully STL Compatible and extremely easy to use with full transparency.
// The entire library is cuvered under the CC0 v1 Universal License.

#ifndef SIML_UTIL
#define SIML_UTIL

#include "image/rgb.hh"
#include <atomic>
#include <cstdint>

namespace siml {
    enum Unit{ // Used by a lots of effects
        PERCENTAGE,
        NEGATIVE_PERCENTAGE,
        NEGATIVE_PIXEL,
        PIXEL,
        INTEGER
    };

    extern std::atomic<uint8_t> total_threads;
    extern std::atomic<uint8_t> active_threads; // Must not be set by the programmer.
}

namespace siml::util {

    double normalize_percentage( // Throws an exception if the entered input was invalid otherwise converts the percentage into unit values ranging from -1.0 to +1.0

        double percentage // for accepting negative inputs.

    );

    uint32_t get_max_possible_values_in_bit_depth(

        unsigned char bitdepth

    ) noexcept;



    // Pixel arithematic starts from here
    
    enum Channel{
        RED,
        BLUE,
        GREEN,
        ALL
    };

    inline void set_pixel(

        RGB_8& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0)
            return;

        const uint32_t max =
            bitdepth >= 8
                ? 255u
                : ((1u << bitdepth) - 1u);

        const uint8_t v =
            value <= 0
                ? uint8_t{0}
                : static_cast<uint64_t>(value) >= max
                    ? static_cast<uint8_t>(max)
                    : static_cast<uint8_t>(value);

        if (channel == RED) {
            if (px.r != v)
                px.r = v;
        }
        else if (channel == GREEN) {
            if (px.g != v)
                px.g = v;
        }
        else if (channel == BLUE) {
            if (px.b != v)
                px.b = v;
        }
        else if (channel == ALL) {
            if (px.r != v)
                px.r = v;

            if (px.g != v)
                px.g = v;

            if (px.b != v)
                px.b = v;
        }
    }


    inline void set_pixel(

        RGB_16& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0)
            return;

        const uint32_t max =
            bitdepth >= 16
                ? 65535u
                : ((1u << bitdepth) - 1u);

        const uint16_t v =
            value <= 0
                ? uint16_t{0}
                : static_cast<uint64_t>(value) >= max
                    ? static_cast<uint16_t>(max)
                    : static_cast<uint16_t>(value);

        if (channel == RED) {
            if (px.r != v)
                px.r = v;
        }
        else if (channel == GREEN) {
            if (px.g != v)
                px.g = v;
        }
        else if (channel == BLUE) {
            if (px.b != v)
                px.b = v;
        }
        else if (channel == ALL) {
            if (px.r != v)
                px.r = v;

            if (px.g != v)
                px.g = v;

            if (px.b != v)
                px.b = v;
        }
    }


    inline void set_pixel(

        RGB_32& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0)
            return;

        const uint64_t max =
            bitdepth >= 32
                ? UINT64_C(4294967295)
                : ((UINT64_C(1) << bitdepth) - UINT64_C(1));

        const uint32_t v =
            value <= 0
                ? uint32_t{0}
                : static_cast<uint64_t>(value) >= max
                    ? static_cast<uint32_t>(max)
                    : static_cast<uint32_t>(value);

        if (channel == RED) {
            if (px.r != v)
                px.r = v;
        }
        else if (channel == GREEN) {
            if (px.g != v)
                px.g = v;
        }
        else if (channel == BLUE) {
            if (px.b != v)
                px.b = v;
        }
        else if (channel == ALL) {
            if (px.r != v)
                px.r = v;

            if (px.g != v)
                px.g = v;

            if (px.b != v)
                px.b = v;
        }
    }


    inline void add_pixel(

        RGB_8& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0 || value <= 0)
            return;

        const uint32_t max =
            bitdepth >= 8
                ? 255u
                : ((1u << bitdepth) - 1u);

        const uint64_t amount = static_cast<uint64_t>(value);

        if (channel == RED) {
            const uint8_t old = px.r;

            if (old < max) {
                const uint8_t v =
                    amount >= static_cast<uint64_t>(max - old)
                        ? static_cast<uint8_t>(max)
                        : static_cast<uint8_t>(old + amount);

                if (old != v)
                    px.r = v;
            }
        }
        else if (channel == GREEN) {
            const uint8_t old = px.g;

            if (old < max) {
                const uint8_t v =
                    amount >= static_cast<uint64_t>(max - old)
                        ? static_cast<uint8_t>(max)
                        : static_cast<uint8_t>(old + amount);

                if (old != v)
                    px.g = v;
            }
        }
        else if (channel == BLUE) {
            const uint8_t old = px.b;

            if (old < max) {
                const uint8_t v =
                    amount >= static_cast<uint64_t>(max - old)
                        ? static_cast<uint8_t>(max)
                        : static_cast<uint8_t>(old + amount);

                if (old != v)
                    px.b = v;
            }
        }
        else if (channel == ALL) {
            if (px.r < max) {
                const uint8_t old = px.r;
                px.r = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint8_t>(max)
                    : static_cast<uint8_t>(old + amount);
            }

            if (px.g < max) {
                const uint8_t old = px.g;
                px.g = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint8_t>(max)
                    : static_cast<uint8_t>(old + amount);
            }

            if (px.b < max) {
                const uint8_t old = px.b;
                px.b = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint8_t>(max)
                    : static_cast<uint8_t>(old + amount);
            }
        }
    }


    inline void subtract_pixel(

        RGB_8& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0 || value <= 0)
            return;

        const uint32_t max =
            bitdepth >= 8
                ? 255u
                : ((1u << bitdepth) - 1u);

        (void)max; // Range maximum is only needed for consistency with add_pixel.

        const uint64_t amount = static_cast<uint64_t>(value);

        if (channel == RED) {
            const uint8_t old = px.r;

            if (old > 0)
                px.r = amount >= old
                    ? uint8_t{0}
                    : static_cast<uint8_t>(old - amount);
        }
        else if (channel == GREEN) {
            const uint8_t old = px.g;

            if (old > 0)
                px.g = amount >= old
                    ? uint8_t{0}
                    : static_cast<uint8_t>(old - amount);
        }
        else if (channel == BLUE) {
            const uint8_t old = px.b;

            if (old > 0)
                px.b = amount >= old
                    ? uint8_t{0}
                    : static_cast<uint8_t>(old - amount);
        }
        else if (channel == ALL) {
            if (px.r > 0) {
                const uint8_t old = px.r;
                px.r = amount >= old
                    ? uint8_t{0}
                    : static_cast<uint8_t>(old - amount);
            }

            if (px.g > 0) {
                const uint8_t old = px.g;
                px.g = amount >= old
                    ? uint8_t{0}
                    : static_cast<uint8_t>(old - amount);
            }

            if (px.b > 0) {
                const uint8_t old = px.b;
                px.b = amount >= old
                    ? uint8_t{0}
                    : static_cast<uint8_t>(old - amount);
            }
        }
    }


    inline void add_pixel(

        RGB_16& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0 || value <= 0)
            return;

        const uint32_t max =
            bitdepth >= 16
                ? 65535u
                : ((1u << bitdepth) - 1u);

        const uint64_t amount = static_cast<uint64_t>(value);

        if (channel == RED) {
            const uint16_t old = px.r;

            if (old < max)
                px.r = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint16_t>(max)
                    : static_cast<uint16_t>(old + amount);
        }
        else if (channel == GREEN) {
            const uint16_t old = px.g;

            if (old < max)
                px.g = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint16_t>(max)
                    : static_cast<uint16_t>(old + amount);
        }
        else if (channel == BLUE) {
            const uint16_t old = px.b;

            if (old < max)
                px.b = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint16_t>(max)
                    : static_cast<uint16_t>(old + amount);
        }
        else if (channel == ALL) {
            if (px.r < max) {
                const uint16_t old = px.r;
                px.r = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint16_t>(max)
                    : static_cast<uint16_t>(old + amount);
            }

            if (px.g < max) {
                const uint16_t old = px.g;
                px.g = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint16_t>(max)
                    : static_cast<uint16_t>(old + amount);
            }

            if (px.b < max) {
                const uint16_t old = px.b;
                px.b = amount >= static_cast<uint64_t>(max - old)
                    ? static_cast<uint16_t>(max)
                    : static_cast<uint16_t>(old + amount);
            }
        }
    }


    inline void subtract_pixel(

        RGB_16& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0 || value <= 0)
            return;

        const uint64_t amount = static_cast<uint64_t>(value);

        if (channel == RED) {
            const uint16_t old = px.r;
            if (old > 0)
                px.r = amount >= old ? uint16_t{0} : static_cast<uint16_t>(old - amount);
        }
        else if (channel == GREEN) {
            const uint16_t old = px.g;
            if (old > 0)
                px.g = amount >= old ? uint16_t{0} : static_cast<uint16_t>(old - amount);
        }
        else if (channel == BLUE) {
            const uint16_t old = px.b;
            if (old > 0)
                px.b = amount >= old ? uint16_t{0} : static_cast<uint16_t>(old - amount);
        }
        else if (channel == ALL) {
            if (px.r > 0) {
                const uint16_t old = px.r;
                px.r = amount >= old ? uint16_t{0} : static_cast<uint16_t>(old - amount);
            }

            if (px.g > 0) {
                const uint16_t old = px.g;
                px.g = amount >= old ? uint16_t{0} : static_cast<uint16_t>(old - amount);
            }

            if (px.b > 0) {
                const uint16_t old = px.b;
                px.b = amount >= old ? uint16_t{0} : static_cast<uint16_t>(old - amount);
            }
        }
    }


    inline void add_pixel(

        RGB_32& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0 || value <= 0)
            return;

        const uint64_t max =
            bitdepth >= 32
                ? UINT64_C(0xFFFFFFFF)
                : ((UINT64_C(1) << bitdepth) - UINT64_C(1));

        const uint64_t amount = static_cast<uint64_t>(value);

        if (channel == RED) {
            const uint32_t old = px.r;

            if (static_cast<uint64_t>(old) < max)
                px.r = amount >= max - old
                    ? static_cast<uint32_t>(max)
                    : static_cast<uint32_t>(old + amount);
        }
        else if (channel == GREEN) {
            const uint32_t old = px.g;

            if (static_cast<uint64_t>(old) < max)
                px.g = amount >= max - old
                    ? static_cast<uint32_t>(max)
                    : static_cast<uint32_t>(old + amount);
        }
        else if (channel == BLUE) {
            const uint32_t old = px.b;

            if (static_cast<uint64_t>(old) < max)
                px.b = amount >= max - old
                    ? static_cast<uint32_t>(max)
                    : static_cast<uint32_t>(old + amount);
        }
        else if (channel == ALL) {
            if (static_cast<uint64_t>(px.r) < max) {
                const uint32_t old = px.r;
                px.r = amount >= max - old
                    ? static_cast<uint32_t>(max)
                    : static_cast<uint32_t>(old + amount);
            }

            if (static_cast<uint64_t>(px.g) < max) {
                const uint32_t old = px.g;
                px.g = amount >= max - old
                    ? static_cast<uint32_t>(max)
                    : static_cast<uint32_t>(old + amount);
            }

            if (static_cast<uint64_t>(px.b) < max) {
                const uint32_t old = px.b;
                px.b = amount >= max - old
                    ? static_cast<uint32_t>(max)
                    : static_cast<uint32_t>(old + amount);
            }
        }
    }


    inline void subtract_pixel(

        RGB_32& px,
        unsigned char bitdepth,
        int64_t value,
        Channel channel = ALL

    ){

        if (bitdepth == 0 || value <= 0)
            return;

        const uint64_t amount = static_cast<uint64_t>(value);

        if (channel == RED) {
            const uint32_t old = px.r;
            if (old > 0)
                px.r = amount >= old ? uint32_t{0} : static_cast<uint32_t>(old - amount);
        }
        else if (channel == GREEN) {
            const uint32_t old = px.g;
            if (old > 0)
                px.g = amount >= old ? uint32_t{0} : static_cast<uint32_t>(old - amount);
        }
        else if (channel == BLUE) {
            const uint32_t old = px.b;
            if (old > 0)
                px.b = amount >= old ? uint32_t{0} : static_cast<uint32_t>(old - amount);
        }
        else if (channel == ALL) {
            if (px.r > 0) {
                const uint32_t old = px.r;
                px.r = amount >= old ? uint32_t{0} : static_cast<uint32_t>(old - amount);
            }

            if (px.g > 0) {
                const uint32_t old = px.g;
                px.g = amount >= old ? uint32_t{0} : static_cast<uint32_t>(old - amount);
            }

            if (px.b > 0) {
                const uint32_t old = px.b;
                px.b = amount >= old ? uint32_t{0} : static_cast<uint32_t>(old - amount);
            }
        }
    }

}

#endif