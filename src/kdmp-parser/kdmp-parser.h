// Axel '0vercl0k' Souchet - February 15 2019
#pragma once
#ifndef _WIN64
#error Only support is for Win 64bits.
#endif

#include "kdmp-parser-structs.h"
#include <cstdint>
#include <tchar.h>
#include <windows.h>

#include <map>

using Physmem_t = std::map<uint64_t, const uint8_t *>;

class KernelDumpParser {
public:

  KernelDumpParser(const TCHAR *PathFile);
  ~KernelDumpParser();

  //
  // Actually do the parsing of the file.
  //

  bool Parse();

  //
  // Give the Context record to the user.
  //

  const KDMP_PARSER_CONTEXT *GetContext();

  const Physmem_t &GetPhysmem();

private:
  //
  // Build a map of physical addresses / page data pointers for full dump.
  //

  bool BuildPhysmemFullDump();

  //
  // Build a map of physical addresses / page data pointers for BMP dump.
  //

  bool BuildPhysmemBMPDump();

  //
  // Parse the DMP_HEADER.
  //

  bool ParseDmpHeader();

  //
  // Map a view of the file in memory.
  //

  bool MapFile();

  //
  // Handle to the input file.
  //

  HANDLE m_File;

  //
  // Handle to the file mapping.
  //

  HANDLE m_FileMap;

  //
  // Base address of the file view.
  //

  PVOID m_ViewBase;

  //
  // Header of the crash-dump.
  //

  KDMP_PARSER_HEADER64 *m_DmpHdr;

  //
  // File path to the crash-dump.
  //

  const TCHAR *m_PathFile;

  //
  // Mapping between physical addresses / page data.
  //

  Physmem_t m_Physmem;
};