#pragma once
#include "Grid.h"
#include "Block.h"
#include <iostream>
#include <string>

class TestCases
{
public:
    // Runs every test and prints a pass/fail summary to stdout.
    // Returns true if ALL tests pass, false otherwise.
    static bool runAll();

private:
    // ── Individual test functions ────────────────────────────
    // Each returns true on pass, false on fail, and prints its
    // own result line.

    // Test 1: moveBlockDown returns false when the block is
    //         sitting on the bottom row of the grid.
    static bool test_moveBlockDown_hitsFloor();

    // Test 2: clearLine removes a full row and reports the
    //         correct line count, then shifts rows down.
    static bool test_clearLine_fullRow();

    // Test 3: isValidPosition returns false when a block
    //         overlaps an already-locked cell.
    static bool test_isValidPosition_overlap();

    // Test 4: lockBlock writes the block's color index into
    //         every cell the block occupies.
    static bool test_lockBlock_writesColor();

    // Test 5: getGhost places the ghost directly above the
    //         floor (or above another locked block) with no
    //         gap and no overshoot.
    static bool test_getGhost_landsCorrectly();

    // ── Helper ───────────────────────────────────────────────
    static void report(const std::string& name, bool passed);
};