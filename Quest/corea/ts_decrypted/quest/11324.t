CNtlTSTrigger
{
	sm = 0;
	sq = 1;
	rq = 0;
	tid = 11324;
	title = -1;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 7;
			prelnk = "5;5;4;3;2;1;";
			nolnk = 8;
			rm = 0;
			yeslnk = 6;

			CDboTSCheckInWorld
			{
				widx = 80000;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "8;6;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;";
			type = 0;
		}
		CDboTSContNarration
		{
			cancellnk = 7;
			cid = 1;
			dt = 2;
			lilnk = 255;
			oklnk = 2;
			ot = 0;
			pt = 0;
			mlt = 10000;
			os = 0;
			prelnk = "0;";
			dg = 1100256;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContNarration
		{
			cancellnk = 7;
			cid = 2;
			dt = 2;
			lilnk = 255;
			oklnk = 3;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 0;
			prelnk = "1;";
			dg = 1100257;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContReward
		{
			nextlnk = 254;
			rwdtype = 1;
			sidx0 = 12007;
			sval0 = 1;
			dtype0 = 2;
			ltime = 60;
			prelnk = "7;";
			sidx1 = 12008;
			stype0 = 0;
			sval1 = 1;
			usetbl = 0;
			sidx2 = 12009;
			stype3 = 4;
			sval2 = 1;
			canclnk = 255;
			cid = 8;
			didx0 = -1;
			dval0 = 127296;
			sidx3 = -1;
			stype2 = 0;
			sval3 = 13440;
			desc = 0;
			rwdtbl = 0;
			stype1 = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSRcvSvrEvt
			{
				id = 13450;
			}
		}
		CDboTSContNarration
		{
			cancellnk = 7;
			cid = 3;
			dt = 2;
			lilnk = 255;
			oklnk = 4;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 0;
			prelnk = "2;";
			dg = 1100258;
			gt = 0;
			oi = 2413109;
		}
		CDboTSContReward
		{
			nextlnk = 254;
			rwdtype = 1;
			sidx0 = 22021;
			sval0 = 1;
			dtype0 = 2;
			ltime = 60;
			prelnk = "7;";
			sidx1 = 22022;
			stype0 = 0;
			sval1 = 1;
			usetbl = 0;
			sidx2 = 22023;
			stype3 = 4;
			sval2 = 1;
			canclnk = 255;
			cid = 6;
			didx0 = -1;
			dval0 = 127296;
			sidx3 = -1;
			stype2 = 0;
			sval3 = 13440;
			desc = 0;
			rwdtbl = 0;
			stype1 = 0;
		}
		CDboTSContNarration
		{
			cancellnk = 7;
			cid = 4;
			dt = 2;
			lilnk = 255;
			oklnk = 5;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 0;
			prelnk = "3;";
			dg = 1100259;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContNarration
		{
			cancellnk = 7;
			cid = 5;
			dt = 2;
			lilnk = 255;
			oklnk = 7;
			ot = 0;
			pt = 2;
			mlt = 5000;
			os = 0;
			prelnk = "4;";
			dg = 1100260;
			gt = 0;
			oi = 7511101;
		}
	}
}

