// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_test.h"
#include "tb_editfield.h"

#ifdef TB_UNIT_TESTING

using namespace tb;

TB_TEST_GROUP(tb_editfield)
{
	TBEditField *edit;
	TBStyleEdit *sedit;

	// == Setup & helpers =====================================================

	TB_TEST(Setup)
	{
		TB_VERIFY(edit = new TBEditField());
		edit->SetMultiline(true);
		sedit = edit->GetStyleEdit();

		/** Set a size so the layout code will be called and we can do some layout tests. */
		edit->SetRect(TBRect(0, 0, 1000, 1000));

		/** Force windows style line breaks so testing is the same on all platforms. */
		sedit->SetWindowsStyleBreak(true);
	}
	TB_TEST(Cleanup) { delete edit; }

	// == Tests ===============================================================

	TB_TEST(settext_singleline)
	{
		edit->SetMultiline(false);
		edit->SetText("One\nTwo", TB_CARET_POS_END);
		TB_VERIFY_STR(edit->GetText(), "One");
	}

	TB_TEST(settext_multiline)
	{
		// Both unix and windows line endings should be ok.
		edit->SetText("One\nTwo", TB_CARET_POS_END);
		TB_VERIFY_STR(edit->GetText(), "One\nTwo");
		edit->SetText("One\r\nTwo", TB_CARET_POS_END);
		TB_VERIFY_STR(edit->GetText(), "One\r\nTwo");
	}

	TB_TEST(settext_singleline_malformed_utf8)
	{
		// Should not detect these sequences as having new line character

		edit->SetText("\xC0\x8A", TB_CARET_POS_END);
		TB_VERIFY(sedit->blocks.CountLinks() == 1);

		edit->SetText("\xE0\x80\x8A", TB_CARET_POS_END);
		TB_VERIFY(sedit->blocks.CountLinks() == 1);

		edit->SetText("\xF0\x80\x80\x8A", TB_CARET_POS_END);
		TB_VERIFY(sedit->blocks.CountLinks() == 1);

		edit->SetText("\xF8\x80\x80\x80\x8A", TB_CARET_POS_END);
		TB_VERIFY(sedit->blocks.CountLinks() == 1);

		edit->SetText("\xFC\x80\x80\x80\x80\x8A", TB_CARET_POS_END);
		TB_VERIFY(sedit->blocks.CountLinks() == 1);

		// Should detect the new line character

		edit->SetText("\xF0\nHello", TB_CARET_POS_END);
		TB_VERIFY(sedit->blocks.CountLinks() == 2);
	}

	TB_TEST(settext_undoredo_ins)
	{
		// 1 character insertions in sequence should be merged to word boundary.
		sedit->InsertText("O"); sedit->InsertText("N"); sedit->InsertText("E"); sedit->InsertText(" ");
		sedit->InsertText("T"); sedit->InsertText("W"); sedit->InsertText("O");
		TB_VERIFY_STR(edit->GetText(), "ONE TWO");

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "ONE ");
		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "");

		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "ONE ");
		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "ONE TWO");

		// 1 character insertions that are multi byte utf8 should also merge.
		// Note: this will also replace "TWO" since redoing keeps the redoed part selected.
		sedit->InsertText("L"); sedit->InsertText("Ö"); sedit->InsertText("K");
		TB_VERIFY_STR(edit->GetText(), "ONE LÖK");
		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "ONE ");
	}

	TB_TEST(settext_undoredo_ins_scattered)
	{
		sedit->InsertText("AAA");
		sedit->caret.SetGlobalOfs(2);
		sedit->InsertText(".");
		sedit->caret.SetGlobalOfs(1);
		sedit->InsertText(".");
		TB_VERIFY_STR(edit->GetText(), "A.A.A");

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "AA.A");
		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "AAA");

		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "AA.A");
		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "A.A.A");
	}

	TB_TEST(settext_undoredo_ins_multiline)
	{
		sedit->InsertText("ONE\nTWO");
		TB_VERIFY_STR(edit->GetText(), "ONE\nTWO");

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "");
		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "ONE\nTWO");
	}

	TB_TEST(settext_undoredo_del)
	{
		sedit->InsertText("ONE TWO");
		sedit->selection.Select(3, 7);
		sedit->selection.RemoveContent();
		TB_VERIFY_STR(edit->GetText(), "ONE");

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "ONE TWO");
		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "ONE");
	}

	TB_TEST(settext_undoredo_ins_linebreak_1)
	{
		sedit->InsertText("ONETWO");
		sedit->caret.SetGlobalOfs(3);
		sedit->InsertText("\n");
		TB_VERIFY_STR(edit->GetText(), "ONE\nTWO");

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "ONETWO");
		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "ONE\nTWO");
	}

	TB_TEST(settext_undoredo_ins_linebreak_2)
	{
		// Inserting a linebreak at the end when we don't end
		// the line with a linebreak character must generate
		// one extra linebreak.
		sedit->InsertBreak();
		TB_VERIFY_STR(edit->GetText(), "\r\n\r\n");

		sedit->InsertBreak();
		TB_VERIFY_STR(edit->GetText(), "\r\n\r\n\r\n");

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "\r\n\r\n");
		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "");
	}

	TB_TEST(settext_undoredo_ins_linebreak_3)
	{
		sedit->SetWindowsStyleBreak(false);

		sedit->InsertBreak();
		TB_VERIFY_STR(edit->GetText(), "\n\n");

		sedit->InsertBreak();
		TB_VERIFY_STR(edit->GetText(), "\n\n\n");

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "\n\n");
		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "");
	}

	TB_TEST(settext_undoredo_ins_linebreak_4)
	{
		sedit->InsertText("ONE");
		sedit->InsertBreak();
		TB_VERIFY_STR(edit->GetText(), "ONE\r\n\r\n");

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "ONE");

		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "ONE\r\n\r\n");
	}

	TB_TEST(settext_undoredo_bugfix1)
	{
		// Make sure we use the test dummy font (ID 0), so we're not dependant on
		// the available fonts & font backend in this test.
		TBFontDescription fd;
		const int font_size = 48;
		fd.SetSize(font_size);
		edit->SetFontDescription(fd);

		sedit->InsertBreak();
		sedit->InsertText("A");
		TB_VERIFY_STR(edit->GetText(), "\r\nA\r\n");
		TB_VERIFY(sedit->GetContentHeight() == font_size * 2);

		sedit->KeyDown(0, TB_KEY_BACKSPACE, TB_MODIFIER_NONE);
		TB_VERIFY_STR(edit->GetText(), "\r\n\r\n");
		TB_VERIFY(sedit->GetContentHeight() == font_size * 2);

		sedit->Undo();
		TB_VERIFY_STR(edit->GetText(), "\r\nA\r\n");
		TB_VERIFY(sedit->GetContentHeight() == font_size * 2);

		sedit->Redo();
		TB_VERIFY_STR(edit->GetText(), "\r\n\r\n");
		TB_VERIFY(sedit->GetContentHeight() == font_size * 2);
	}

	TB_TEST(settext_insert_linebreaks_move)
	{
		sedit->InsertText("Foo\n");
		sedit->InsertText("Foo\n");
		sedit->InsertText("Foo\n");
		TB_VERIFY_STR(edit->GetText(), "Foo\nFoo\nFoo\n");
	}

	TB_TEST(multiline_overflow_1)
	{
		// Make sure we use the test dummy font (ID 0), so we're not dependant on
		// the available fonts & font backend in this test.
		TBFontDescription fd;
		const int font_size = 48;
		fd.SetSize(font_size);
		edit->SetFontDescription(fd);

		// Test that a long line that overflow but has no allowed break position doesn't wrap.
		edit->SetText("this_is_a_long_line_that_should_not_wrap\n"
						"this_is_a_long_line_that_should_not_wrap", TB_CARET_POS_END);
		TB_VERIFY(sedit->GetContentHeight() == font_size * 2);
	}
}

#endif // TB_UNIT_TESTING
