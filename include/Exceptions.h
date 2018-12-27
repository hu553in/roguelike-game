/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_EXCEPTIONS_H_
#define INCLUDE_EXCEPTIONS_H_


#include <exception>

namespace Exceptions {
    namespace FileExceptions {
        class FileCantBeOpenException : public std::exception {
         public:
            FileCantBeOpenException();

            ~FileCantBeOpenException() override;
        };

        class CorruptedFileException : public std::exception {
         public:
            CorruptedFileException();

            ~CorruptedFileException() override;
        };
    }

    namespace StorageExceptions {
        class EntryNotFoundException : public std::exception {
         public:
            EntryNotFoundException();

            ~EntryNotFoundException() override;
        };

        class InvalidTypeIDException : public std::exception {
         public:
            InvalidTypeIDException();

            ~InvalidTypeIDException() override;
        };

        class EntryAlreadyExistsException : public std::exception {
         public:
            EntryAlreadyExistsException();

            ~EntryAlreadyExistsException() override;
        };
    }
}

#endif  // INCLUDE_EXCEPTIONS_H_
