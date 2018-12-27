/* Copyright (C) 2018 hu553in */

#include <Exceptions.h>

Exceptions::FileExceptions::FileCantBeOpenException::FileCantBeOpenException() = default;

Exceptions::FileExceptions::FileCantBeOpenException::~FileCantBeOpenException() = default;

Exceptions::FileExceptions::CorruptedFileException::CorruptedFileException() = default;

Exceptions::FileExceptions::CorruptedFileException::~CorruptedFileException() = default;

Exceptions::StorageExceptions::EntryNotFoundException::EntryNotFoundException() = default;

Exceptions::StorageExceptions::EntryNotFoundException::~EntryNotFoundException() = default;

Exceptions::StorageExceptions::InvalidTypeIDException::InvalidTypeIDException() = default;

Exceptions::StorageExceptions::InvalidTypeIDException::~InvalidTypeIDException() = default;

Exceptions::StorageExceptions::EntryAlreadyExistsException::EntryAlreadyExistsException() = default;

Exceptions::StorageExceptions::EntryAlreadyExistsException::~EntryAlreadyExistsException() = default;
