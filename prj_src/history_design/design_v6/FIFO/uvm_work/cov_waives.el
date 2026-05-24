// VCS Exclusion File
// Waive unreachable skid buffer state (0, 1) in async_fifo_top
block : "async_fifo_top"
{
    line : 253
    {
        cond : "((( !g_fwft_reg_mode.rdata_valid )) || rinc || (( !g_fwft_reg_mode.skid_valid )))"
        {
            exclude : "1 0 0" ; // Exclude state [1, 0, 0]
            reason : "Unreachable Skid Buffer state: rdata_valid=0 and skid_valid=1 is physically impossible." ;
        }
    }
}