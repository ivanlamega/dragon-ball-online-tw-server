CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 770;
	title = 77002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 77009;
				ctype = 1;
				idx = 3032101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 77008;
				gtype = 1;
				area = 77001;
				goal = 77004;
				grade = 132203;
				rwd = 100;
				sort = 77005;
				stype = 1;
				taid = 1;
				title = 77002;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 77007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3032101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 33;
				minlvl = 25;
			}
			CDboTSCheckClrQst
			{
				and = "769;";
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
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 77008;
			gtype = 1;
			oklnk = 2;
			area = 77001;
			goal = 77004;
			sort = 77005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 77002;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 77014;
			nextlnk = 254;
			rwdtbl = 77001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7132101;
			}
		}
	}
}

