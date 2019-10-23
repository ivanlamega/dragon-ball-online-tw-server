CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1350;
	title = 135002;

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
			stdiag = 135007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5313201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1349;";
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
				conv = 135009;
				ctype = 1;
				idx = 5313201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 135008;
				m1fx = "2348.000000";
				area = 135001;
				goal = 135004;
				m0fz = "4786.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 135016;
				sort = 135005;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "4714.000000";
				grade = 132203;
				m0fx = "2675.000000";
				m0ttip = 135015;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 135002;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 16;
				eitype = 0;
				idx0 = 7411101;
				cnt0 = 16;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 7412100;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 135014;
			nextlnk = 101;
			rwdtbl = 135001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5313201;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 135008;
			gtype = 2;
			oklnk = 2;
			area = 135001;
			goal = 135004;
			sort = 135005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 135002;
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

