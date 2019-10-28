CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1275;
	title = 127502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 127508;
			gtype = 2;
			oklnk = 2;
			area = 127501;
			goal = 127504;
			sort = 127505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 127502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 127514;
			nextlnk = 101;
			rwdtbl = 127501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 848;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 127507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSCheckClrQst
			{
				and = "1272;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 127509;
				ctype = 1;
				idx = 2611102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 127508;
				m1fx = "1672.000000";
				m2fz = "3478.000000";
				m1fy = "0.000000";
				sort = 127505;
				m2widx = 1;
				grade = 132203;
				m0fx = "1994.000000";
				m0ttip = 127515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 127502;
				gtype = 2;
				area = 127501;
				goal = 127504;
				m0fz = "3568.000000";
				m0widx = 1;
				m1ttip = 127516;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "2743.000000";
				m2fx = "2000.000000";
				m2ttip = 127517;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 848;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 848;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 127507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 848;
				taid = 1;
				type = 1;
			}
		}
	}
}

