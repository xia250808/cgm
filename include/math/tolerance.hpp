

namespace cgm::math {
	template<typename T>
	struct Tolerance
	{
		static constexpr T value() {
			return T(0);
		}

	};

	template<>
	struct Tolerance<float> {
		static constexpr float value() {
			return 1e-6f;
		}
	};

	template<>
	struct Tolerance<double> {
		static constexpr double value() {
			return 1e-12;
		}
	};

	template<>
	struct Tolerance<long double> {
		static constexpr long double value() {
			return 1e-15l;
		}
	};

	template<typename T>
	bool is_zero(T value) {
		return std::abs(value) <= Tolerance<T>::value();
	}

}