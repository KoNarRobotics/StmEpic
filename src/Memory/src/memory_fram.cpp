#include "memory_fram.hpp"
#include "device.hpp"
#include "sha256.hpp"
#include "stm32f4xx_hal_i2c.h"
#include "stmepic.hpp"
#include "stmepic_status.hpp"
#include "device.hpp"
#include <cstdint>
#include <cstdlib>

using namespace stmepic::memory;
using namespace stmepic;


FRAM::FRAM()
{
  encryption_key = base_encryption_key;
}

Result<std::vector<uint8_t>> FRAM::encode_data(const std::vector<uint8_t> &data)
{
  if(data.size() == 0) return Status::CapacityError("Size of the data is 0");

  uint32_t encres = stmepic::Ticker::get_instance().get_micros();
  uint16_t checksum = calculate_checksum(data);
  // auto mayby_encrypted_data = encrypt_data(data, encryption_key, encres);
  STMEPIC_ASSING_OR_RETURN(encrypted_data,encrypt_data(data, encryption_key, encres));

  std::vector<uint8_t> da;
  da.resize(data.size() + frame_size);
  da[0] = magic_number_1;
  da[1] = (checksum >> 8) & 0xFF;
  da[2] = checksum & 0xFF;
  da[3] = (encres >> 24) & 0xFF;
  da[4] = (encres >> 16) & 0xFF;
  da[5] = (encres >> 8) & 0xFF;
  da[6] = encres & 0xFF;
  da[7] = (encrypted_data.size() >> 8) & 0xFF;
  da[8] = encrypted_data.size() & 0xFF;
  da[9] = magic_number_2;
  for(size_t i = 0; i < encrypted_data.size(); i++) da[i + 10] = encrypted_data[i];
  return Result<std::vector<uint8_t>>::OK(da);
}

Result<std::vector<uint8_t>> FRAM::decode_data(const std::vector<uint8_t> &data)
{
  if(data.size() == 0) return Status::CapacityError("Size of the data is 0");

  uint8_t mg1 = data[0];
  uint16_t checksum = (data[1] << 8) | data[2];
  uint32_t encres = (data[3] << 24) | (data[4] << 16) | (data[5] << 8) | data[6];
  uint16_t size = (data[7] << 8) | data[8];
  uint8_t mg2 = data[9];
  if(mg1 != magic_number_1) return Status::Invalid("Magic number 1 is not correct");
  if(mg2 != magic_number_2) return Status::Invalid("Magic number 2 is not correct");
  if(size != data.size() - frame_size) return Status::Invalid("Size is not correct");

  auto data_data = std::vector<uint8_t>(data.begin() + frame_size, data.end());
  STMEPIC_ASSING_OR_RETURN(decrypted_data,decrypt_data(data_data, encryption_key, encres));
  if(calculate_checksum(decrypted_data) != checksum) return Status::Invalid("Checksum is not correct");
  return Result<decltype(decrypted_data)>::OK(decrypted_data);
}


uint16_t FRAM::calculate_checksum(const std::vector<uint8_t> &data)
{
  uint16_t checksum = 0;
  for(auto &d : data) checksum += d;
  return checksum;
}

Result<std::vector<uint8_t>> FRAM::encrypt_data(const std::vector<uint8_t> &data, uint32_t key, uint32_t encres)
{
  if(data.size() == 0) return Status::CapacityError("Size of the data is 0");
  if(key == base_encryption_key) return Result<std::vector<uint8_t>>::OK(data);
  std::vector<uint8_t> encrypted_data;
  uint8_t shaout[algorithm::SHA256::SHA256_OUTPUT_SIZE];
  uint32_t key_data[] = {key, encres};
  algorithm::SHA256::sha256((uint8_t*)(&key_data), 8, shaout);
  for(size_t i = 0; i < data.size(); i++) encrypted_data.push_back(data[i] ^ shaout[i % algorithm::SHA256::SHA256_OUTPUT_SIZE]);
  return Result<std::vector<uint8_t>>::OK(encrypted_data);
}

Result<std::vector<uint8_t>> FRAM::decrypt_data(const std::vector<uint8_t> &data, uint32_t key, uint32_t encres)
{
  if(data.size() == 0) return Status::CapacityError("Size of the data is 0");
  if(key == base_encryption_key) return Result<std::vector<uint8_t>>::OK(data);
  std::vector<uint8_t> decrypted_data;
  uint8_t shaout[algorithm::SHA256::SHA256_OUTPUT_SIZE];
  uint32_t key_data[] = {key, encres};
  algorithm::SHA256::sha256((uint8_t*)(&key_data), 8, shaout);
  for(size_t i = 0; i < data.size(); i++) decrypted_data.push_back(data[i] ^ shaout[i % algorithm::SHA256::SHA256_OUTPUT_SIZE]);
  return Result<std::vector<uint8_t>>::OK(decrypted_data);
}

void FRAM::set_encryption_key(uint32_t key)
{
  encryption_key = key;
}

uint32_t FRAM::get_encryption_key()
{
  return encryption_key;
}


