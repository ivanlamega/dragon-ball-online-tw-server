CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1804;
	title = 180402;

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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 180409;
				ctype = 1;
				idx = 3031210;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 180408;
				gtype = 2;
				area = 180401;
				goal = 180404;
				m0fz = "976.000000";
				m0widx = 1;
				sort = 180405;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "3951.000000";
				m0ttip = 180415;
				rwd = 100;
				taid = 1;
				title = 180402;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 3613100;
				cnt0 = 25;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 180414;
			nextlnk = 101;
			rwdtbl = 180401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031210;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 180407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031210;
			}
			CDboTSCheckLvl
			{
				maxlvl = 39;
				minlvl = 31;
			}
			CDboTSCheckClrQst
			{
				and = "1803;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 180408;
			gtype = 2;
			oklnk = 2;
			area = 180401;
			goal = 180404;
			sort = 180405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 180402;
		}
	}
}

