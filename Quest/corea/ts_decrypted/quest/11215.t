CNtlTSTrigger
{
	sm = 0;
	sq = 1;
	rq = 0;
	tid = 11215;
	title = -1;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "6;4;";
			type = 1;
		}
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "1;2;3;3;";
			nolnk = 6;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckInWorld
			{
				widx = 28000;
			}
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
				id = 12500;
			}
		}
		CDboTSContNarration
		{
			cancellnk = 5;
			cid = 3;
			dt = 0;
			lilnk = 255;
			oklnk = 5;
			ot = 0;
			pt = 2;
			mlt = 10000;
			os = 0;
			prelnk = "2;";
			dg = 1100183;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;";
			type = 0;
		}
		CDboTSContNarration
		{
			cancellnk = 5;
			cid = 2;
			dt = 0;
			lilnk = 255;
			oklnk = 3;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 0;
			prelnk = "1;";
			dg = 1100177;
			gt = 0;
			oi = 2413109;
		}
		CDboTSContReward
		{
			nextlnk = 254;
			rwdtype = 1;
			sidx0 = 12021;
			sval0 = 1;
			dtype0 = 2;
			ltime = 60;
			prelnk = "5;";
			sidx1 = 12022;
			stype0 = 0;
			sval1 = 1;
			usetbl = 0;
			sidx2 = 12023;
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
			cancellnk = 5;
			cid = 1;
			dt = 0;
			lilnk = 255;
			oklnk = 2;
			ot = 0;
			pt = 0;
			mlt = 10000;
			os = 0;
			prelnk = "0;";
			dg = 1100176;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContReward
		{
			nextlnk = 254;
			rwdtype = 1;
			sidx0 = 22017;
			sval0 = 1;
			dtype0 = 2;
			ltime = 60;
			prelnk = "5;";
			sidx1 = 22018;
			stype0 = 0;
			sval1 = 1;
			usetbl = 0;
			sidx2 = 22019;
			stype3 = 4;
			sval2 = 1;
			canclnk = 255;
			cid = 4;
			didx0 = -1;
			dval0 = 103896;
			sidx3 = -1;
			stype2 = 0;
			sval3 = 10800;
			desc = 0;
			rwdtbl = 0;
			stype1 = 0;
		}
	}
}

