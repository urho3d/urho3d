// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_TEST_H
#define TB_TEST_H

/**
	This file contains a very simple unit testing framework.

	There are more capable unit testing frameworks available (that
	might be more suitable if you need extensive testing of your target
	application.

	I've chosen to not use any other framework for internal testing of
	Turbo Badger to minimize dependences.

	Test groups and tests:
	---------------------

	Tests are specified in named groups, that can contain multiple named tests
	that are run in the order specified, except for special tests.

	Special tests are test with the names Init, Shutdown, Setup, Cleanup.
	They can be left out if they are not needed.

	Init and Shutdown - Called once per group. If Init fail, the tests in the
						group and Shutdown will be skipped.
	Setup and Cleanup - Called once per test. If Setup fail, the current test
						and Cleanup will be skipped.

	How to define a single test:
	---------------------------

	TB_TEST_GROUP(groupname)
	{
		TB_TEST(testname)
		{
			// Here goes test code and calls
			// to TB_VERIFY, TB_PASS, TB_FAIL etc.
			TB_VERIFY(1);
		}
	}

	How to define multiple tests, with data, setup and cleanup:
	----------------------------------------------------------

	TB_TEST_GROUP(groupname)
	{
		// Here goes the data for this group
		TBStr str;

		// Here goes methods with access to data
		bool is_str_empty() { return str.IsEmpty(); }

		// A test with name Setup will be called before each test.
		// If it fail, no other tests will be called (not even Cleanup).
		TB_TEST(Setup)
		{
			// Setup
		}

		// The actual test code. Will be called if Setup passed.
		TB_TEST(test_something_1)
		{
			// Test 1
		}

		// Another test code. Will be called if Setup passed.
		TB_TEST(test_something_2)
		{
			// Test 2
		}

		// A test with name Cleanup will be called after each test.
		// Will be called even if the test failed.
		TB_TEST(Cleanup)
		{
			// Cleanup
		}
	}
*/

#include "tb_types.h"
#include "tb_linklist.h"
#include "tb_str.h"
#include <math.h>

namespace tb {

/** Setting for TBRunTests to print out more information. */
#define TB_TEST_VERBOSE				1

#ifdef TB_UNIT_TESTING

/** Run the tests. Return the number of fails. */
int TBRunTests(uint32 settings = TB_TEST_VERBOSE);

/** Verify that the expression is true and fail if it isn't. */
#define TB_VERIFY(expr) { fail_line_nr = __LINE__; fail_file = __FILE__; if (!(expr)) { fail_text = (#expr); return; } }

/** Verify that the values are approximately the same. */
#define TB_VERIFY_FLOAT(val, ref_val) { TB_VERIFY(fabs(ref_val - val) < 1.0E-5); }

/** Verify that the strings are equal. */
#define TB_VERIFY_STR(str1, str2) { TB_VERIFY(strcmp(str1, str2) == 0); }

/** End the test with a pass. */
#define TB_PASS() return;

/** End the test with a description why it failed. */
#define TB_FAIL(error) { fail_line_nr = __LINE__; fail_file = __FILE__; fail_text = error; return; }

/** Return a absolute path for the given filename relative to the test source file. */
#define TB_TEST_FILE(filename) tb_get_test_file_name(__FILE__, filename)

/** TBCall is used to execute callbacks for tests in TBTestGroup. */
class TBCall : public TBLinkOf<TBCall>
{
public:
	/** return the name of the call */
	virtual const char *name() = 0;
	/** execute the test code */
	virtual void exec() = 0;
};

/** TBTestGroup has a collection of callbacks for tests, and optional Setup and Cleanup calls. */
class TBTestGroup
{
public:
	TBTestGroup(const char *name);
	bool IsSpecialTest(TBCall *call) const { return !call->linklist; }
public:
	const char *name;		///< Test group name.
	TBCall *setup;			///< Setup call, or nullptr.
	TBCall *cleanup;		///< Cleanup call, or nullptr.
	TBCall *init;			///< Init call, or nullptr.
	TBCall *shutdown;		///< Shutdown call, or nullptr.
	TBLinkListOf<TBCall> calls;///< All test calls to call.
	TBTestGroup *next_test_group;
};

/** TBRegisterCall is used for registering calls on TBTestGroup .*/
class TBRegisterCall
{
public:
	TBRegisterCall(TBTestGroup *test, TBCall *call);
	~TBRegisterCall();
private:
	TBCall *call;
};

#define TB_TEST_GROUP(name) \
	namespace testgroup_##name \
	{ \
		class TheGroup : public TBTestGroup \
		{ \
		public: \
			TheGroup() : TBTestGroup(#name) {} \
		}; \
		TheGroup the_group_obj; \
		int force_link = 0; \
	} \
	namespace testgroup_##name \

#define TB_TEST(callname) \
			class CallObj##callname : public TBCall \
			{ \
			public: \
				virtual const char *name(); \
				virtual void exec(); \
			}; \
			CallObj##callname callname; \
			TBRegisterCall callname##reg(&the_group_obj, &callname); \
			const char *CallObj##callname::name() { return #callname; } \
			void CallObj##callname::exec()

/** Hack to force linking the given test group.
	This might be needed for test groups in source files that contain
	nothing else that's referenced by the application, and which are
	linked in an library. */
#define TB_FORCE_LINK_TEST_GROUP(name) \
	namespace testgroup_##name { void force_link_call() { extern int force_link; force_link = 1; }}

TBStr tb_get_test_file_name(const char *testpath, const char *filename);

// Internal globals
extern uint32 test_settings;	///< Settings, as sent to TBRunTests
extern int fail_line_nr;		///< Fail line number
extern const char *fail_file;	///< Fail file name
extern const char *fail_text;	///< Fail text description

#else

inline int TBRunTests(uint32 settings = TB_TEST_VERBOSE) { return 0; }

#endif

}; // namespace tb

#endif // TB_TEST_H
