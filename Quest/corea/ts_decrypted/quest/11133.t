CNtlTSTrigger
{
	sm = 0;
	sq = 0;
	rq = 0;
	tid = 11133;
	title = -1;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 9;
			prelnk = "6;";
			nolnk = 8;
			rm = 0;
			yeslnk = 7;

			CDboTSCheckInWorld
			{
				widx = 11000;
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
				id = 11490;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "8;7;";
			type = 1;
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
			os = 2;
			prelnk = "0;";
			dg = 1100924;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;";
			type = 0;
		}
		CDboTSContReward
		{
			nextlnk = 254;
			rwdtype = 1;
			sidx0 = 12017;
			sval0 = 1;
			dtype0 = 2;
			ltime = 60;
			prelnk = "9;";
			sidx1 = 12018;
			stype0 = 0;
			sval1 = 1;
			usetbl = 0;
			sidx2 = 12019;
			stype3 = 4;
			sval2 = 1;
			canclnk = 255;
			cid = 8;
			didx0 = -1;
			dval0 = 138528;
			sidx3 = -1;
			stype2 = 0;
			sval3 = 14400;
			desc = 0;
			rwdtbl = 0;
			stype1 = 0;
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 6;
			prelnk = "3;2;1;4;4;";

			CDboTSActSendSvrEvt
			{
				id = 11500;
				tblidx = -1;
				stradius = 0;
				stype = 0;
				taid = 1;
				ttype = 255;
				type = 1;
			}
		}
		CDboTSContReward
		{
			nextlnk = 254;
			rwdtype = 1;
			sidx0 = 22004;
			sval0 = 1;
			dtype0 = 2;
			ltime = 60;
			prelnk = "9;";
			sidx1 = 22005;
			stype0 = 0;
			sval1 = 0;
			usetbl = 0;
			sidx2 = 22006;
			stype3 = 4;
			sval2 = 0;
			canclnk = 255;
			cid = 7;
			didx0 = -1;
			dval0 = 106912;
			sidx3 = -1;
			stype2 = 0;
			sval3 = 10720;
			desc = 0;
			rwdtbl = 0;
			stype1 = 0;
		}
		CDboTSContNarration
		{
			cancellnk = 5;
			cid = 4;
			dt = 0;
			lilnk = 255;
			oklnk = 5;
			ot = 0;
			pt = 2;
			mlt = 10000;
			os = 2;
			prelnk = "3;";
			dg = 1100927;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContNarration
		{
			cancellnk = 5;
			cid = 3;
			dt = 0;
			lilnk = 255;
			oklnk = 4;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 2;
			prelnk = "2;";
			dg = 1100926;
			gt = 0;
			oi = 7511101;
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
			dg = 1100925;
			gt = 0;
			oi = 2413109;
		}
		CDboTSContGCond
		{
			cid = 6;
			prelnk = "5;";
			nolnk = 255;
			rm = 0;
			yeslnk = 9;

			CDboTSRcvSvrEvt
			{
				id = 11510;
			}
		}
	}
}

