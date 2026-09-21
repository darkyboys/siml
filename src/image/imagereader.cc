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

#include "../../image/imagereader.hh"

#include <array>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace siml {

	/*
		============================================================
			PNG constants
		============================================================
	*/

	static constexpr uint8_t PNG_SIGNATURE[8] =
	{
		137, 80, 78, 71,
		13, 10, 26, 10
	};


	/*
		============================================================
			Big-endian helpers

			PNG stores multi-byte integers in big-endian order.
		============================================================
	*/

	static uint16_t read_u16_be(
		const uint8_t* data)
	{
		return static_cast<uint16_t>(
			(static_cast<uint16_t>(data[0]) << 8) |
			static_cast<uint16_t>(data[1])
		);
	}


	static uint32_t read_u32_be(
		const uint8_t* data)
	{
		return
			(static_cast<uint32_t>(data[0]) << 24) |
			(static_cast<uint32_t>(data[1]) << 16) |
			(static_cast<uint32_t>(data[2]) << 8) |
			static_cast<uint32_t>(data[3]);
	}


	static void write_u16_be(
		std::vector<uint8_t>& output,
		uint16_t value)
	{
		output.push_back(
			static_cast<uint8_t>(
				(value >> 8) & 0xFF
			)
		);

		output.push_back(
			static_cast<uint8_t>(
				value & 0xFF
			)
		);
	}


	static void write_u32_be(
		std::vector<uint8_t>& output,
		uint32_t value)
	{
		output.push_back(
			static_cast<uint8_t>(
				(value >> 24) & 0xFF
			)
		);

		output.push_back(
			static_cast<uint8_t>(
				(value >> 16) & 0xFF
			)
		);

		output.push_back(
			static_cast<uint8_t>(
				(value >> 8) & 0xFF
			)
		);

		output.push_back(
			static_cast<uint8_t>(
				value & 0xFF
			)
		);
	}


	/*
		============================================================
			CRC32

			PNG requires CRC32 for every chunk.
		============================================================
	*/

	class CRC32
	{
	private:

		std::array<uint32_t, 256> table{};

	public:

		CRC32()
		{
			for (uint32_t i = 0; i < 256; ++i)
			{
				uint32_t value = i;

				for (int bit = 0; bit < 8; ++bit)
				{
					if (value & 1u)
					{
						value =
							0xEDB88320u ^
							(value >> 1);
					}
					else
					{
						value >>= 1;
					}
				}

				table[i] = value;
			}
		}


		uint32_t operator()(
			const uint8_t* data,
			std::size_t size) const
		{
			uint32_t crc = 0xFFFFFFFFu;

			for (std::size_t i = 0; i < size; ++i)
			{
				crc =
					table[
						(crc ^ data[i]) & 0xFFu
					] ^
					(crc >> 8);
			}

			return crc ^ 0xFFFFFFFFu;
		}
	};


	/*
		============================================================
			Adler32

			zlib stores this checksum after the DEFLATE stream.
		============================================================
	*/

	static uint32_t adler32(
		const std::vector<uint8_t>& data)
	{
		constexpr uint32_t MOD = 65521;

		uint32_t a = 1;
		uint32_t b = 0;

		for (uint8_t byte : data)
		{
			a += byte;

			if (a >= MOD)
				a -= MOD;

			b += a;

			if (b >= MOD)
				b -= MOD;
		}

		return (b << 16) | a;
	}


	/*
		============================================================
			DEFLATE bit reader

			DEFLATE reads bits from least-significant bit first.
		============================================================
	*/

	class BitReader
	{
	private:

		const std::vector<uint8_t>& data;

		std::size_t byte_position = 0;

		uint32_t bit_buffer = 0;
		unsigned bits_in_buffer = 0;

	public:

		explicit BitReader(
			const std::vector<uint8_t>& input)
			: data(input)
		{
		}


		uint32_t read_bits(
			unsigned count)
		{
			if (count == 0)
				return 0;

			if (count > 24)
				throw std::runtime_error(
					"SIML: BitReader request is too large."
				);

			while (bits_in_buffer < count)
			{
				if (byte_position >= data.size())
				{
					throw std::runtime_error(
						"SIML: Unexpected end of DEFLATE stream."
					);
				}

				bit_buffer |=
					static_cast<uint32_t>(
						data[byte_position++]
					) << bits_in_buffer;

				bits_in_buffer += 8;
			}

			const uint32_t mask =
				(1u << count) - 1u;

			const uint32_t result =
				bit_buffer & mask;

			bit_buffer >>= count;
			bits_in_buffer -= count;

			return result;
		}


		void align_to_byte()
		{
			bit_buffer = 0;
			bits_in_buffer = 0;
		}
	};


	/*
		============================================================
			Huffman tree
		============================================================
	*/

	class HuffmanTree
	{
	private:

		struct Entry
		{
			uint32_t code = 0;
			uint16_t symbol = 0;
			uint8_t length = 0;
		};

		std::vector<Entry> entries;


		static uint32_t reverse_bits(
			uint32_t value,
			unsigned count)
		{
			uint32_t result = 0;

			for (unsigned i = 0; i < count; ++i)
			{
				result <<= 1;
				result |= value & 1u;
				value >>= 1;
			}

			return result;
		}

	public:

		void build(
			const std::vector<uint8_t>& lengths)
		{
			entries.clear();

			unsigned maximum_length = 0;

			for (uint8_t length : lengths)
			{
				if (length > maximum_length)
					maximum_length = length;
			}

			if (maximum_length == 0)
			{
				throw std::runtime_error(
					"SIML: Empty Huffman tree."
				);
			}

			std::vector<unsigned> count(
				maximum_length + 1,
				0
			);

			for (uint8_t length : lengths)
			{
				if (length != 0)
					++count[length];
			}

			std::vector<unsigned> next_code(
				maximum_length + 1,
				0
			);

			unsigned code = 0;

			for (unsigned bits = 1;
				bits <= maximum_length;
				++bits)
			{
				code =
					(code + count[bits - 1]) << 1;

				next_code[bits] = code;
			}

			for (uint16_t symbol = 0;
				symbol < lengths.size();
				++symbol)
			{
				const uint8_t length =
					lengths[symbol];

				if (length == 0)
					continue;

				const uint32_t canonical =
					next_code[length]++;

				Entry entry;

				entry.code =
					reverse_bits(
						canonical,
						length
					);

				entry.symbol = symbol;
				entry.length = length;

				entries.push_back(entry);
			}
		}


		uint16_t decode(
			BitReader& reader) const
		{
			uint32_t code = 0;

			for (unsigned length = 1;
				length <= 15;
				++length)
			{
				code |=
					reader.read_bits(1)
					<< (length - 1);

				for (const Entry& entry : entries)
				{
					if (
						entry.length == length &&
						entry.code == code
					)
					{
						return entry.symbol;
					}
				}
			}

			throw std::runtime_error(
				"SIML: Invalid Huffman code."
			);
		}
	};


	/*
		============================================================
			DEFLATE decoder
		============================================================
	*/

	class DeflateDecoder
	{
	private:

		static constexpr int length_base[29] =
		{
			3, 4, 5, 6, 7, 8, 9, 10,
			11, 13, 15, 17,
			19, 23, 27, 31,
			35, 43, 51, 59,
			67, 83, 99, 115,
			131, 163, 195, 227,
			258
		};

		static constexpr int length_extra[29] =
		{
			0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 1, 1,
			2, 2, 2, 2,
			3, 3, 3, 3,
			4, 4, 4, 4,
			5, 5, 5, 5,
			0
		};

		static constexpr int distance_base[30] =
		{
			1, 2, 3, 4,
			5, 7, 9, 13,
			17, 25, 33, 49,
			65, 97, 129, 193,
			257, 385, 513, 769,
			1025, 1537, 2049, 3073,
			4097, 6145, 8193, 12289,
			16385, 24577
		};

		static constexpr int distance_extra[30] =
		{
			0, 0, 0, 0,
			1, 1, 2, 2,
			3, 3, 4, 4,
			5, 5, 6, 6,
			7, 7, 8, 8,
			9, 9, 10, 10,
			11, 11, 12, 12,
			13, 13
		};


		static HuffmanTree fixed_literal_tree()
		{
			std::vector<uint8_t> lengths(288);

			for (int i = 0; i <= 143; ++i)
				lengths[i] = 8;

			for (int i = 144; i <= 255; ++i)
				lengths[i] = 9;

			for (int i = 256; i <= 279; ++i)
				lengths[i] = 7;

			for (int i = 280; i <= 287; ++i)
				lengths[i] = 8;

			HuffmanTree tree;

			tree.build(lengths);

			return tree;
		}


		static HuffmanTree fixed_distance_tree()
		{
			std::vector<uint8_t> lengths(
				32,
				5
			);

			HuffmanTree tree;

			tree.build(lengths);

			return tree;
		}


		static void decode_huffman_block(
			BitReader& reader,
			const HuffmanTree& literal_tree,
			const HuffmanTree& distance_tree,
			std::vector<uint8_t>& output)
		{
			while (true)
			{
				const uint16_t symbol =
					literal_tree.decode(reader);

				if (symbol <= 255)
				{
					output.push_back(
						static_cast<uint8_t>(
							symbol
						)
					);

					continue;
				}

				if (symbol == 256)
					break;

				if (symbol < 257 ||
					symbol > 285)
				{
					throw std::runtime_error(
						"SIML: Invalid DEFLATE length symbol."
					);
				}

				const int length_index =
					symbol - 257;

				int length =
					length_base[length_index];

				const int length_bits =
					length_extra[length_index];

				if (length_bits != 0)
				{
					length += static_cast<int>(
						reader.read_bits(
							length_bits
						)
					);
				}

				const uint16_t distance_symbol =
					distance_tree.decode(reader);

				if (distance_symbol >= 30)
				{
					throw std::runtime_error(
						"SIML: Invalid DEFLATE distance symbol."
					);
				}

				int distance =
					distance_base[
						distance_symbol
					];

				const int distance_bits =
					distance_extra[
						distance_symbol
					];

				if (distance_bits != 0)
				{
					distance += static_cast<int>(
						reader.read_bits(
							distance_bits
						)
					);
				}

				if (
					distance <= 0 ||
					static_cast<std::size_t>(
						distance
					) > output.size()
				)
				{
					throw std::runtime_error(
						"SIML: Invalid DEFLATE back-reference."
					);
				}

				for (int i = 0;
					i < length;
					++i)
				{
					const std::size_t source =
						output.size() -
						static_cast<std::size_t>(
							distance
						);

					output.push_back(
						output[source]
					);
				}
			}
		}


		static void decode_dynamic_block(
			BitReader& reader,
			std::vector<uint8_t>& output)
		{
			const unsigned HLIT =
				reader.read_bits(5) + 257;

			const unsigned HDIST =
				reader.read_bits(5) + 1;

			const unsigned HCLEN =
				reader.read_bits(4) + 4;

			if (HLIT > 286 ||
				HDIST > 32)
			{
				throw std::runtime_error(
					"SIML: Invalid dynamic Huffman sizes."
				);
			}

			static constexpr int order[19] =
			{
				16, 17, 18,
				0, 8, 7, 9, 6,
				10, 5, 11, 4,
				12, 3, 13, 2,
				14, 1, 15
			};

			std::vector<uint8_t> code_lengths(
				19,
				0
			);

			for (unsigned i = 0;
				i < HCLEN;
				++i)
			{
				code_lengths[order[i]] =
					static_cast<uint8_t>(
						reader.read_bits(3)
					);
			}

			HuffmanTree code_length_tree;

			code_length_tree.build(
				code_lengths
			);

			std::vector<uint8_t> lengths;

			lengths.reserve(
				HLIT + HDIST
			);

			while (lengths.size() <
				HLIT + HDIST)
			{
				const uint16_t symbol =
					code_length_tree.decode(
						reader
					);

				if (symbol <= 15)
				{
					lengths.push_back(
						static_cast<uint8_t>(
							symbol
						)
					);
				}
				else if (symbol == 16)
				{
					if (lengths.empty())
					{
						throw std::runtime_error(
							"SIML: Invalid Huffman repeat."
						);
					}

					const unsigned repeat =
						reader.read_bits(2) + 3;

					const uint8_t previous =
						lengths.back();

					for (unsigned i = 0;
						i < repeat;
						++i)
					{
						lengths.push_back(
							previous
						);
					}
				}
				else if (symbol == 17)
				{
					const unsigned repeat =
						reader.read_bits(3) + 3;

					for (unsigned i = 0;
						i < repeat;
						++i)
					{
						lengths.push_back(0);
					}
				}
				else if (symbol == 18)
				{
					const unsigned repeat =
						reader.read_bits(7) + 11;

					for (unsigned i = 0;
						i < repeat;
						++i)
					{
						lengths.push_back(0);
					}
				}
				else
				{
					throw std::runtime_error(
						"SIML: Invalid Huffman code-length symbol."
					);
				}

				if (lengths.size() >
					HLIT + HDIST)
				{
					throw std::runtime_error(
						"SIML: Huffman code-length overflow."
					);
				}
			}

			std::vector<uint8_t> literal_lengths(
				lengths.begin(),
				lengths.begin() + HLIT
			);

			std::vector<uint8_t> distance_lengths(
				lengths.begin() + HLIT,
				lengths.end()
			);

			bool has_distance_code = false;

			for (uint8_t length : distance_lengths)
			{
				if (length != 0)
				{
					has_distance_code = true;
					break;
				}
			}

			if (!has_distance_code)
			{
				throw std::runtime_error(
					"SIML: Dynamic DEFLATE distance tree is empty."
				);
			}

			HuffmanTree literal_tree;
			HuffmanTree distance_tree;

			literal_tree.build(
				literal_lengths
			);

			distance_tree.build(
				distance_lengths
			);

			decode_huffman_block(
				reader,
				literal_tree,
				distance_tree,
				output
			);
		}

	public:

		std::vector<uint8_t> decode(
			const std::vector<uint8_t>& compressed)
		{
			if (compressed.size() < 6)
			{
				throw std::runtime_error(
					"SIML: Invalid zlib stream."
				);
			}

			const uint8_t CMF =
				compressed[0];

			const uint8_t FLG =
				compressed[1];

			if ((CMF & 0x0F) != 8)
			{
				throw std::runtime_error(
					"SIML: PNG data does not use DEFLATE."
				);
			}

			if (
				(
					(static_cast<unsigned>(CMF) << 8) |
					FLG
				) % 31 != 0
			)
			{
				throw std::runtime_error(
					"SIML: Invalid zlib header."
				);
			}

			if (FLG & 0x20)
			{
				throw std::runtime_error(
					"SIML: Preset zlib dictionaries are unsupported."
				);
			}

			std::vector<uint8_t> deflate(
				compressed.begin() + 2,
				compressed.end() - 4
			);

			BitReader reader(deflate);

			std::vector<uint8_t> output;

			bool final_block = false;

			while (!final_block)
			{
				final_block =
					reader.read_bits(1) != 0;

				const unsigned block_type =
					reader.read_bits(2);

				if (block_type == 0)
				{
					reader.align_to_byte();

					const uint16_t length =
						static_cast<uint16_t>(
							reader.read_bits(16)
						);

					const uint16_t inverse =
						static_cast<uint16_t>(
							reader.read_bits(16)
						);

					if (
						static_cast<uint16_t>(
							length ^ 0xFFFFu
						) != inverse
					)
					{
						throw std::runtime_error(
							"SIML: Invalid stored DEFLATE block."
						);
					}

					for (uint16_t i = 0;
						i < length;
						++i)
					{
						output.push_back(
							static_cast<uint8_t>(
								reader.read_bits(8)
							)
						);
					}
				}
				else if (block_type == 1)
				{
					HuffmanTree literal_tree =
						fixed_literal_tree();

					HuffmanTree distance_tree =
						fixed_distance_tree();

					decode_huffman_block(
						reader,
						literal_tree,
						distance_tree,
						output
					);
				}
				else if (block_type == 2)
				{
					decode_dynamic_block(
						reader,
						output
					);
				}
				else
				{
					throw std::runtime_error(
						"SIML: Reserved DEFLATE block type."
					);
				}
			}

			const uint32_t expected_adler =
				read_u32_be(
					compressed.data() +
					compressed.size() -
					4
				);

			const uint32_t actual_adler =
				adler32(output);

			if (expected_adler != actual_adler)
			{
				throw std::runtime_error(
					"SIML: Adler32 checksum mismatch."
				);
			}

			return output;
		}
	};


	/*
		============================================================
			PNG filter reconstruction
		============================================================
	*/

	static uint8_t paeth_predictor(
		uint8_t left,
		uint8_t up,
		uint8_t upper_left)
	{
		const int p =
			static_cast<int>(left) +
			static_cast<int>(up) -
			static_cast<int>(upper_left);

		const int pa =
			std::abs(
				p - static_cast<int>(left)
			);

		const int pb =
			std::abs(
				p - static_cast<int>(up)
			);

		const int pc =
			std::abs(
				p - static_cast<int>(upper_left)
			);

		if (pa <= pb && pa <= pc)
			return left;

		if (pb <= pc)
			return up;

		return upper_left;
	}


	static void unfilter_row(
		uint8_t filter,
		std::vector<uint8_t>& row,
		const std::vector<uint8_t>& previous,
		std::size_t bytes_per_pixel)
	{
		if (filter > 4)
		{
			throw std::runtime_error(
				"SIML: Invalid PNG filter."
			);
		}

		for (std::size_t i = 0;
			i < row.size();
			++i)
		{
			const uint8_t left =
				(i >= bytes_per_pixel)
					? row[i - bytes_per_pixel]
					: 0;

			const uint8_t up =
				previous.empty()
					? 0
					: previous[i];

			const uint8_t upper_left =
				(
					i >= bytes_per_pixel &&
					!previous.empty()
				)
					? previous[i - bytes_per_pixel]
					: 0;

			switch (filter)
			{
				case 0:
					break;

				case 1:
					row[i] =
						static_cast<uint8_t>(
							row[i] + left
						);
					break;

				case 2:
					row[i] =
						static_cast<uint8_t>(
							row[i] + up
						);
					break;

				case 3:
					row[i] =
						static_cast<uint8_t>(
							row[i] +
							(
								static_cast<unsigned>(left) +
								static_cast<unsigned>(up)
							) / 2
						);
					break;

				case 4:
					row[i] =
						static_cast<uint8_t>(
							row[i] +
							paeth_predictor(
								left,
								up,
								upper_left
							)
						);
					break;
			}
		}
	}


	/*
		============================================================
			PNG chunk creation
		============================================================
	*/

	static void append_png_chunk(
		std::vector<uint8_t>& png,
		const char type[4],
		const std::vector<uint8_t>& data)
	{
		if (
			data.size() >
			std::numeric_limits<uint32_t>::max()
		)
		{
			throw std::runtime_error(
				"SIML: PNG chunk is too large."
			);
		}

		write_u32_be(
			png,
			static_cast<uint32_t>(
				data.size()
			)
		);

		const std::size_t type_position =
			png.size();

		for (int i = 0; i < 4; ++i)
		{
			png.push_back(
				static_cast<uint8_t>(
					type[i]
				)
			);
		}

		png.insert(
			png.end(),
			data.begin(),
			data.end()
		);

		CRC32 crc;

		const uint32_t checksum =
			crc(
				png.data() + type_position,
				4 + data.size()
			);

		write_u32_be(
			png,
			checksum
		);
	}


	/*
		============================================================
			ImageReader
		============================================================
	*/

	Image ImageReader::read(
		const std::string& filename) const
	{
		std::ifstream file(
			filename,
			std::ios::binary
		);

		if (!file)
		{
			throw std::runtime_error(
				"SIML: Could not open file: " +
				filename
			);
		}

		std::vector<uint8_t> png(
			(
				std::istreambuf_iterator<char>(
					file
				)
			),
			std::istreambuf_iterator<char>()
		);

		if (png.size() < 8)
		{
			throw std::runtime_error(
				"SIML: File is too small to be a PNG."
			);
		}

		for (int i = 0; i < 8; ++i)
		{
			if (png[i] != PNG_SIGNATURE[i])
			{
				throw std::runtime_error(
					"SIML: Invalid PNG signature."
				);
			}
		}

		std::size_t position = 8;

		uint32_t width = 0;
		uint32_t height = 0;

		uint8_t bit_depth = 0;
		uint8_t color_type = 0;
		uint8_t compression_method = 0;
		uint8_t filter_method = 0;
		uint8_t interlace_method = 0;

		bool have_IHDR = false;
		bool have_IDAT = false;
		bool have_IEND = false;

		std::vector<uint8_t> compressed_data;

		CRC32 crc;

		while (position < png.size())
		{
			if (png.size() - position < 12)
			{
				throw std::runtime_error(
					"SIML: Truncated PNG chunk."
				);
			}

			const uint32_t chunk_length =
				read_u32_be(
					png.data() + position
				);

			position += 4;

			if (
				static_cast<std::size_t>(
					chunk_length
				) >
				png.size() - position - 8
			)
			{
				throw std::runtime_error(
					"SIML: PNG chunk extends beyond file."
				);
			}

			const uint8_t* type =
				png.data() + position;

			position += 4;

			const std::size_t data_position =
				position;

			position += chunk_length;

			const uint32_t stored_crc =
				read_u32_be(
					png.data() + position
				);

			position += 4;

			std::vector<uint8_t> crc_data;

			crc_data.reserve(
				4 + chunk_length
			);

			for (int i = 0; i < 4; ++i)
			{
				crc_data.push_back(
					type[i]
				);
			}

			crc_data.insert(
				crc_data.end(),
				png.begin() + data_position,
				png.begin() +
					data_position +
					chunk_length
			);

			const uint32_t calculated_crc =
				crc(
					crc_data.data(),
					crc_data.size()
				);

			if (calculated_crc != stored_crc)
			{
				throw std::runtime_error(
					"SIML: PNG chunk CRC mismatch."
				);
			}


			/*
				IHDR
			*/

			if (
				type[0] == 'I' &&
				type[1] == 'H' &&
				type[2] == 'D' &&
				type[3] == 'R'
			)
			{
				if (have_IHDR)
				{
					throw std::runtime_error(
						"SIML: Multiple IHDR chunks."
					);
				}

				if (chunk_length != 13)
				{
					throw std::runtime_error(
						"SIML: Invalid IHDR size."
					);
				}

				const uint8_t* data =
					png.data() +
					data_position;

				width =
					read_u32_be(data);

				height =
					read_u32_be(data + 4);

				bit_depth = data[8];
				color_type = data[9];
				compression_method = data[10];
				filter_method = data[11];
				interlace_method = data[12];

				if (width == 0 ||
					height == 0)
				{
					throw std::runtime_error(
						"SIML: Image dimensions cannot be zero."
					);
				}

				/*
					Color type 2:

						RGB

					Color type 6:

						RGBA

					We explicitly reject RGBA because
					SIML::Image currently has no alpha channel.
				*/

				if (color_type == 6)
				{
					throw std::runtime_error(
						"SIML: RGBA images are not supported."
					);
				}

				if (color_type != 2)
				{
					throw std::runtime_error(
						"SIML: Only RGB PNG images are supported."
					);
				}

				if (bit_depth != 8 &&
					bit_depth != 16)
				{
					throw std::runtime_error(
						"SIML: Only 8-bit and 16-bit RGB images are supported."
					);
				}

				if (compression_method != 0)
				{
					throw std::runtime_error(
						"SIML: Unsupported PNG compression method."
					);
				}

				if (filter_method != 0)
				{
					throw std::runtime_error(
						"SIML: Unsupported PNG filter method."
					);
				}

				if (interlace_method != 0)
				{
					throw std::runtime_error(
						"SIML: Interlaced PNGs are not supported."
					);
				}

				have_IHDR = true;
			}


			/*
				IDAT
			*/

			else if (
				type[0] == 'I' &&
				type[1] == 'D' &&
				type[2] == 'A' &&
				type[3] == 'T'
			)
			{
				if (!have_IHDR)
				{
					throw std::runtime_error(
						"SIML: IDAT appears before IHDR."
					);
				}

				have_IDAT = true;

				compressed_data.insert(
					compressed_data.end(),
					png.begin() + data_position,
					png.begin() +
						data_position +
						chunk_length
				);
			}


			/*
				tRNS

				This introduces transparency semantics.
				SIML currently does not represent alpha.
			*/

			else if (
				type[0] == 't' &&
				type[1] == 'R' &&
				type[2] == 'N' &&
				type[3] == 'S'
			)
			{
				throw std::runtime_error(
					"SIML: Transparent RGB images are not supported."
				);
			}


			/*
				IEND
			*/

			else if (
				type[0] == 'I' &&
				type[1] == 'E' &&
				type[2] == 'N' &&
				type[3] == 'D'
			)
			{
				if (chunk_length != 0)
				{
					throw std::runtime_error(
						"SIML: IEND must have zero-length data."
					);
				}

				have_IEND = true;
				break;
			}
		}

		if (!have_IHDR)
		{
			throw std::runtime_error(
				"SIML: Missing IHDR."
			);
		}

		if (!have_IDAT)
		{
			throw std::runtime_error(
				"SIML: Missing IDAT."
			);
		}

		if (!have_IEND)
		{
			throw std::runtime_error(
				"SIML: Missing IEND."
			);
		}


		/*
			Decode zlib + DEFLATE.
		*/

		DeflateDecoder decoder;

		std::vector<uint8_t> raw =
			decoder.decode(
				compressed_data
			);


		/*
			Calculate scanline dimensions.
		*/

		const std::size_t bytes_per_channel =
			bit_depth / 8;

		const std::size_t bytes_per_pixel =
			3 * bytes_per_channel;

		const std::size_t row_bytes =
			static_cast<std::size_t>(width) *
			bytes_per_pixel;

		const std::size_t expected_size =
			static_cast<std::size_t>(height) *
			(row_bytes + 1);

		if (raw.size() != expected_size)
		{
			throw std::runtime_error(
				"SIML: Decompressed image size is invalid."
			);
		}


		/*
			Create Image.

			8-bit:

				RGB_8

			16-bit:

				RGB_16
		*/

		Image image;

		image.width = width;
		image.height = height;
		image.bitdepth = bit_depth;

		const std::size_t pixel_count =
			static_cast<std::size_t>(width) *
			static_cast<std::size_t>(height);

		if (bit_depth == 8)
		{
			image.pixels_8bit.resize(
				pixel_count
			);
		}
		else
		{
			image.pixels_16bit.resize(
				pixel_count
			);
		}


		/*
			Reconstruct scanlines.
		*/

		std::vector<uint8_t> previous_row(
			row_bytes,
			0
		);

		std::size_t raw_position = 0;

		for (uint32_t y = 0;
			y < height;
			++y)
		{
			const uint8_t filter =
				raw[raw_position++];

			std::vector<uint8_t> row(
				raw.begin() + raw_position,
				raw.begin() +
					raw_position +
					row_bytes
			);

			raw_position += row_bytes;

			unfilter_row(
				filter,
				row,
				previous_row,
				bytes_per_pixel
			);


			if (bit_depth == 8)
			{
				for (uint32_t x = 0;
					x < width;
					++x)
				{
					const std::size_t source =
						static_cast<std::size_t>(x) * 3;

					const std::size_t destination =
						static_cast<std::size_t>(y) *
						width +
						x;

					RGB_8& pixel =
						image.pixels_8bit[
							destination
						];

					pixel.r =
						row[source];

					pixel.g =
						row[source + 1];

					pixel.b =
						row[source + 2];
				}
			}
			else
			{
				for (uint32_t x = 0;
					x < width;
					++x)
				{
					const std::size_t source =
						static_cast<std::size_t>(x) * 6;

					const std::size_t destination =
						static_cast<std::size_t>(y) *
						width +
						x;

					RGB_16& pixel =
						image.pixels_16bit[
							destination
						];

					pixel.r =
						read_u16_be(
							row.data() +
							source
						);

					pixel.g =
						read_u16_be(
							row.data() +
							source +
							2
						);

					pixel.b =
						read_u16_be(
							row.data() +
							source +
							4
						);
				}
			}

			previous_row =
				std::move(row);
		}

		return image;
	}


	/*
		============================================================
			ImageWriter helpers
		============================================================
	*/

	static std::vector<uint8_t>
	make_uncompressed_zlib(
		const std::vector<uint8_t>& raw)
	{
		std::vector<uint8_t> output;

		/*
			zlib header.

			0x78 = DEFLATE + 32 KiB window.
			0x01 = no compression / fastest.
		*/

		output.push_back(0x78);
		output.push_back(0x01);

		std::size_t position = 0;

		do
		{
			const std::size_t remaining =
				raw.size() - position;

			const uint16_t block_size =
				static_cast<uint16_t>(
					remaining > 65535
						? 65535
						: remaining
				);

			const bool final_block =
				position + block_size ==
				raw.size();


			/*
				Stored DEFLATE block.

				BFINAL:

					1 = last block

				BTYPE:

					00 = stored
			*/

			output.push_back(
				final_block
					? 0x01
					: 0x00
			);

			output.push_back(
				static_cast<uint8_t>(
					block_size & 0xFF
				)
			);

			output.push_back(
				static_cast<uint8_t>(
					(block_size >> 8) & 0xFF
				)
			);

			const uint16_t inverse =
				static_cast<uint16_t>(
					~block_size
				);

			output.push_back(
				static_cast<uint8_t>(
					inverse & 0xFF
				)
			);

			output.push_back(
				static_cast<uint8_t>(
					(inverse >> 8) & 0xFF
				)
			);


			/*
				Copy bytes directly.

				No compression takes place here.
			*/

			output.insert(
				output.end(),
				raw.begin() + position,
				raw.begin() +
					position +
					block_size
			);

			position += block_size;

		} while (position < raw.size());


		/*
			zlib trailer:

				Adler32 of uncompressed data.
		*/

		write_u32_be(
			output,
			adler32(raw)
		);

		return output;
	}


	/*
		============================================================
			ImageWriter
		============================================================
	*/

	void ImageWriter::write(
		const Image& image,
		const std::string& filename) const
	{
		if (image.width == 0 ||
			image.height == 0)
		{
			throw std::runtime_error(
				"SIML: Cannot write an empty image."
			);
		}

		if (image.bitdepth != 8 &&
			image.bitdepth != 16)
		{
			throw std::runtime_error(
				"SIML: Only 8-bit and 16-bit RGB images are supported."
			);
		}

		const std::size_t pixel_count =
			static_cast<std::size_t>(
				image.width
			) *
			static_cast<std::size_t>(
				image.height
			);

		if (image.bitdepth == 8)
		{
			if (
				image.pixels_8bit.size() !=
				pixel_count
			)
			{
				throw std::runtime_error(
					"SIML: RGB_8 pixel count does not match image dimensions."
				);
			}
		}
		else
		{
			if (
				image.pixels_16bit.size() !=
				pixel_count
			)
			{
				throw std::runtime_error(
					"SIML: RGB_16 pixel count does not match image dimensions."
				);
			}
		}


		/*
			Build raw PNG scanlines.

			Every row uses filter type 0.

			Therefore the scanline contains the raw RGB
			values directly.
		*/

		const std::size_t bytes_per_channel =
			image.bitdepth / 8;

		const std::size_t bytes_per_pixel =
			3 * bytes_per_channel;

		const std::size_t row_bytes =
			static_cast<std::size_t>(
				image.width
			) *
			bytes_per_pixel;

		std::vector<uint8_t> raw;

		raw.reserve(
			static_cast<std::size_t>(
				image.height
			) *
			(row_bytes + 1)
		);

		for (uint32_t y = 0;
			y < image.height;
			++y)
		{
			/*
				PNG filter:

					0 = None
			*/

			raw.push_back(0);

			for (uint32_t x = 0;
				x < image.width;
				++x)
			{
				const std::size_t index =
					static_cast<std::size_t>(y) *
					image.width +
					x;

				if (image.bitdepth == 8)
				{
					const RGB_8& pixel =
						image.pixels_8bit[
							index
						];

					raw.push_back(pixel.r);
					raw.push_back(pixel.g);
					raw.push_back(pixel.b);
				}
				else
				{
					const RGB_16& pixel =
						image.pixels_16bit[
							index
						];

					write_u16_be(
						raw,
						pixel.r
					);

					write_u16_be(
						raw,
						pixel.g
					);

					write_u16_be(
						raw,
						pixel.b
					);
				}
			}
		}


		/*
			Start PNG.
		*/

		std::vector<uint8_t> png;

		png.insert(
			png.end(),
			PNG_SIGNATURE,
			PNG_SIGNATURE + 8
		);


		/*
			IHDR

			Color type 2 = RGB.
		*/

		std::vector<uint8_t> ihdr;

		write_u32_be(
			ihdr,
			image.width
		);

		write_u32_be(
			ihdr,
			image.height
		);

		ihdr.push_back(
			image.bitdepth
		);

		/*
			2 = Truecolor RGB.
		*/

		ihdr.push_back(2);

		/*
			Compression method = 0
			Filter method      = 0
			Interlace          = 0
		*/

		ihdr.push_back(0);
		ihdr.push_back(0);
		ihdr.push_back(0);

		append_png_chunk(
			png,
			"IHDR",
			ihdr
		);


		/*
			IDAT

			raw
				↓
			zlib
				↓
			stored DEFLATE blocks
				↓
			IDAT

			No actual compression.
		*/

		std::vector<uint8_t> zlib_data =
			make_uncompressed_zlib(
				raw
			);

		constexpr std::size_t MAX_IDAT_CHUNK =
			1024 * 1024;

		std::size_t position = 0;

		while (position < zlib_data.size())
		{
			const std::size_t remaining =
				zlib_data.size() -
				position;

			const std::size_t amount =
				remaining > MAX_IDAT_CHUNK
					? MAX_IDAT_CHUNK
					: remaining;

			std::vector<uint8_t> chunk(
				zlib_data.begin() + position,
				zlib_data.begin() +
					position +
					amount
			);

			append_png_chunk(
				png,
				"IDAT",
				chunk
			);

			position += amount;
		}


		/*
			IEND
		*/

		std::vector<uint8_t> empty;

		append_png_chunk(
			png,
			"IEND",
			empty
		);


		/*
			Write PNG to disk.
		*/

		std::ofstream file(
			filename,
			std::ios::binary
		);

		if (!file)
		{
			throw std::runtime_error(
				"SIML: Could not create output file: " +
				filename
			);
		}

		file.write(
			reinterpret_cast<const char*>(
				png.data()
			),
			static_cast<std::streamsize>(
				png.size()
			)
		);

		if (!file)
		{
			throw std::runtime_error(
				"SIML: Failed while writing PNG."
			);
		}
	}

} // namespace siml
