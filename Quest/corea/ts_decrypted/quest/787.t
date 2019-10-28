CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 787;
	title = 78702;

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
				conv = 78709;
				ctype = 1;
				idx = 1351209;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 78708;
				gtype = 1;
				area = 78701;
				goal = 78704;
				grade = 132203;
				rwd = 100;
				sort = 78705;
				stype = 1;
				taid = 1;
				title = 78702;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 78707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1351209;
			}
			CDboTSCheckLvl
			{
				maxlvl = 34;
				minlvl = 26;
			}
			CDboTSCheckClrQst
			{
				and = "786;";
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
			cont = 78708;
			gtype = 1;
			oklnk = 2;
			area = 78701;
			goal = 78704;
			sort = 78705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 78702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 78714;
			nextlnk = 254;
			rwdtbl = 78701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312109;
			}
		}
	}
}

