CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 734;
	title = 73402;

	CNtlTSGroup
	{
		gid = 0;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 73407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4191110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 32;
				minlvl = 24;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 73414;
			nextlnk = 101;
			rwdtbl = 73401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7131111;
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
				conv = 73409;
				ctype = 1;
				idx = 4191110;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 73408;
				m1fx = "5836.000000";
				m2fz = "-32.000000";
				m1fy = "0.000000";
				sort = 73405;
				m2widx = 1;
				grade = 132203;
				m0fx = "4540.000000";
				m0ttip = 73415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 73402;
				gtype = 2;
				area = 73401;
				goal = 73404;
				m0fz = "65.000000";
				m0widx = 1;
				m1ttip = 73416;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "2037.000000";
				m2fx = "7285.000000";
				m2ttip = 73417;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 1412105;
				cnt0 = 18;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
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
				eitype = 0;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 73408;
			gtype = 2;
			oklnk = 2;
			area = 73401;
			goal = 73404;
			sort = 73405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 73402;
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
				itype = 0;
			}
		}
	}
}
