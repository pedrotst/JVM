class ClassFile {
      uint32_t magic;
      uint16_t minor_version;
      uint16_t major_version;
      uint32_t constant_pool_count;
      std::vector<cp_info> constant_pool;
      uint16_t access_flags;
      uint16_t this_class;
      uint16_t super_class;
      uint16_t interfaces_count;
      std::vector<uint16_t> interfaces;
      uint16_t fields_count;
      std::vector<field_info> fields;
      uint16_t methods_count;
      std::vector<method_info> methods;
      uint16_t attributes_count;
      std::vector<attribute_info> attributes;
}
