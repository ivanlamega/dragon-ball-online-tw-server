CNtlTSTrigger
{
	sm = 0;
	sq = 1;
	rq = 0;
	tid = 11427;
	title = -1;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 7;
			prelnk = "5;";
			nolnk = 8;
			rm = 0;
			yeslnk = 6;

			CDboTSCheckInWorld
			{
				widx = 130000;
			}
		}
		CDboTSContNarration
		{
			cancellnk = 4;
			cid = 3;
			dt = 2;
			lilnk = 255;
			oklnk = 4;
			ot = 0;
			pt = 2;
			mlt = 10000;
			os = 0;
			prelnk = "2;";
			dg = 1100369;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContNarration
		{
			cancellnk = 4;
			cid = 2;
			dt = 2;
			lilnk = 255;
			oklnk = 3;
			ot = 0;
			pt = 1;
			mlt = 10000;
			os = 0;
			prelnk = "1;";
			dg = 1100368;
			gt = 0;
			oi = 7511101;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "3;2;3;1;";

			CDboTSActSendSvrEvt
			{
				id = 14720;
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
			sidx0 = 22007;
			sval0 = 1;
			dtype0 = 2;
			ltime = 60;
			prelnk = "7;";
			sidx1 = 22008;
			stype0 = 0;
			sval1 = 1;
			usetbl = 0;
			sidx2 = 22009;
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
		CDboTSContReward
		{
			nextlnk = 254;
			rwdtype = 1;
			sidx0 = 22027;
			sval0 = 1;
			dtype0 = 2;
			ltime = 60;
			prelnk = "7;";
			sidx1 = 22028;
			stype0 = 0;
			sval1 = 1;
			usetbl = 0;
			sidx2 = 22029;
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
		CDboTSContGCond
		{
			cid = 5;
			prelnk = "4;";
			nolnk = 255;
			rm = 0;
			yeslnk = 7;

			CDboTSRcvSvrEvt
			{
				id = 14730;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "8;6;";
			type = 1;
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
				id = 14710;
			}
		}
		CDboTSContNarration
		{
			cancellnk = 4;
			cid = 1;
			dt = 2;
			lilnk = 255;
			oklnk = 2;
			ot = 0;
			pt = 0;
			mlt = 10000;
			os = 0;
			prelnk = "0;";
			dg = 1100367;
			gt = 0;
			oi = 7511101;
		}
	}
}

