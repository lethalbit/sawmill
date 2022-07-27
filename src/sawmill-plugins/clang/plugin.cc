/* SPDX-License-Identifier: BSD-3-Clause */
/* clang/plugin.cc - Sawmill instrumentation plugin for clang */

#include <clang/AST/ASTContext.h>
#include <clang/AST/Attr.h>
#include <clang/Sema/ParsedAttr.h>
#include <clang/Sema/SemaDiagnostic.h>
#include <llvm/IR/Attributes.h>


struct SawmillAttrInfo : public clang::ParsedAttrInfo {

	SawmillAttrInfo() {
		OptArgs = 15;

		static constexpr Spelling attrs[] = {
			{clang::ParsedAttr::AS_CXX11, "sawmill::instrument"}
		};

		Spellings = attrs;
	}
};


[[maybe_unused]]
static clang::ParsedAttrInfoRegistry::Add<SawmillAttrInfo> X(
	"instrument",
	"Sawmill structured logging instrumentation"
);
