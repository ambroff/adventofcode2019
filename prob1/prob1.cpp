#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <cmath>
#include <system_error>
#include <string>
#include <vector>

double fuel_requirement(double mass) {
    return std::floor(mass / 3.0) - 2;
}

double fixed_fuel_requirement(double mass) {
    if (mass <= 0) {
        return 0;
    }

    auto required = fuel_requirement(mass);
    return required + std::max(0.0, fixed_fuel_requirement(required));
}

void load_input(const std::string& input_file_name,
                std::vector<double>& input_list,
                std::error_code& ec)
{
    ec.clear();

    std::ifstream input_stream;
    input_stream.open(input_file_name, std::ios::in);
    if (input_stream.fail()) {
        ec = make_error_code(static_cast<std::errc>(errno));
        return;
    }

    for (std::string line; std::getline(input_stream, line); ) {
        input_list.push_back(std::stoi(line));
    }
}

TEST_CASE("Part 1 test input", "[prob1]") {
  REQUIRE(fuel_requirement(12.0) == 2.0);
  REQUIRE(fuel_requirement(14.0) == 2.0);
  REQUIRE(fuel_requirement(1969.0) == 654.0);
  REQUIRE(fuel_requirement(100756.0) == 33583);
}

TEST_CASE("Part 1 solution", "[prob1]") {
    std::vector<double> inputs;
    std::error_code ec;

    load_input("input.txt", inputs, ec);
    REQUIRE(!ec);
    REQUIRE(inputs.size() == 100);

    double sum = 0;
    for (auto input : inputs) {
        sum += fuel_requirement(input);
    }

    REQUIRE(sum == 3324332.0);
}

TEST_CASE("Part 2 test input", "[prob1]") {
  REQUIRE(fixed_fuel_requirement(12.0) == 2.0);
  REQUIRE(fixed_fuel_requirement(14.0) == 2.0);
  REQUIRE(fixed_fuel_requirement(1969.0) == 966.0);
  REQUIRE(fixed_fuel_requirement(100756.0) == 50346.0);
}

TEST_CASE("Part 2 solution", "[prob1]") {
  std::vector<double> inputs;
  std::error_code ec;

  load_input("input.txt", inputs, ec);
  REQUIRE(!ec);
  REQUIRE(inputs.size() == 100);

  double sum = 0;
  for (auto input : inputs) {
    sum += fixed_fuel_requirement(input);
  }

  REQUIRE(sum == 4983626.0);
}
